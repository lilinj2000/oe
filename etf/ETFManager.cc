
#include "ETFManager.hh"
#include "ETFConnectionPool.hh"
#include "CRImpl.hh"
#include "NSCCImpl.hh"
#include "VolumeDailyImpl.hh"
#include "VolatilityDailyImpl.hh"
#include "ETFUtils.hh"

namespace oe
{

ETFManager::ETFManager(const std::string& dbhost, const std::string& user, const std::string& password, const std::string& db)
{
  conn_pool_.reset(new ETFConnectionPool(dbhost, user, password, db));
  try {
    mysqlpp::ScopedConnection cp(*conn_pool_, true);
    if (!cp->thread_aware())
    {
      std::cerr << "MySQL++ wasn't built with thread awareness!  " << std::endl;
      throw mysqlpp::ObjectNotInitialized("MySQL wasnt' built with thread awareness!");
    }
  }
  catch (mysqlpp::Exception& e) {
    std::cerr << "Failed to set up initial pooled connection: " <<
        e.what() << std::endl;
    throw;
  }

  cr_.reset(new CRImpl());
  nscc_.reset(new NSCCImpl());
  volumedaily_.reset(new VolumeDailyImpl());
  volatilitydaily_.reset(new VolatilityDailyImpl());
  
  utils_.reset(new ETFUtils());
}

ETFManager::~ETFManager()
{
}

void ETFManager::fetchTradingInfo(TradingInfo& theTradingInfo)
{
  theTradingInfo.clear();
  
  try
  {
    mysqlpp::ScopedConnection scoped_conn(*conn_pool_, true);
    
    // step1. get the today's cu info
    CUInfo todayCU;
    nscc_->fetchCUInfoToday(*scoped_conn, todayCU);

    // 1.1 change to TradingInfo
    TradingInfo todayTradingInfo;
    utils_->toTradingInfo(todayCU, todayTradingInfo);

    // step2. get the lastWorkDay's cu info
    CUInfo lastCU;
    nscc_->fetchCUInfoLastWorkDay(*scoped_conn, lastCU);

    // 2.1 to TradingInfo 
    TradingInfo lastTradingInfo;
    utils_->toTradingInfo(lastCU, lastTradingInfo);

    // 2.2 merge today - yesterday per ticker
    TradingInfo realTradingInfo;
    utils_->mergeTradingInfo(todayTradingInfo, lastTradingInfo, realTradingInfo);

    // step3. get the today's cr info
    CRInfoList todayCRInfoList;
    cr_->fetchCRInfoList(*scoped_conn, todayCRInfoList);

    // 3.1 calculate the final trading quantity
    utils_->calFinalTradingInfo(todayTradingInfo, todayCRInfoList, realTradingInfo);

    // 4.1 fetch the volume info
    volumedaily_->fetchTickerVolumeInfo(*scoped_conn, realTradingInfo);

    // 4.2 fetch the volatility info
    volatilitydaily_->fetchTickerVolatilityInfo(*scoped_conn, realTradingInfo);

    // output the real trading info
    theTradingInfo = realTradingInfo;
    
  }
  catch (mysqlpp::Exception& e)
  {
    std::cerr <<"db failed." <<std::endl;
  }
  catch(std::exception& e)
  {
    std::cerr <<"exception catched: " <<e.what() <<std::endl;
  }

  return;
}


} // namespace oe
