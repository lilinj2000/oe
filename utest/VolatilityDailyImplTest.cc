#include <stdlib.h>
#include <string>
#include <memory>

#include "mysql++.h"
#include "gtest/gtest.h"

#include "etf/VolatilityDailyImpl.hh"
#include "etf/ETFUtils.hh"


class VolatilityDailyImplTest : public ::testing::Test
{
 public:
  void SetUp()
  {
    conn_.reset(new mysqlpp::Connection("ETF", "localhost", "test", "test"));
    volatilitydaily_.reset(new oe::VolatilityDailyImpl());

    utils_.reset(new oe::ETFUtils());
    // prepareData();
  }

  
 protected:
  void prepareData()
  {
      if( system("mysql -utest -ptest ETF < dailyuse.sql")<0 )
      {
        std::cerr <<"load dailyuse failed." <<std::endl;
        exit(-1);
      }

      mysqlpp::Query query = conn_->query();

      query <<"update dailyuse set date=curdate()";
      mysqlpp::SimpleResult res = query.execute();

  }
  
  std::auto_ptr<mysqlpp::Connection> conn_;
  std::auto_ptr<oe::VolatilityDailyImpl> volatilitydaily_;
  std::auto_ptr<oe::ETFUtils> utils_;
};


TEST_F(VolatilityDailyImplTest, testFetchTickerVolatilityInfo)
{
  oe::TradingInfo tradingInfo;
  oe::TickerInfo tickerInfo;

  tickerInfo.quantity_ = 6;
  tradingInfo["IF1506"] = tickerInfo;

  tickerInfo.quantity_ = 7;
  tradingInfo["IF1507"] = tickerInfo;

  volatilitydaily_->fetchTickerVolatilityInfo(*conn_, tradingInfo);

  utils_->outputTradingInfo(tradingInfo);
  
  EXPECT_TRUE(2==tradingInfo.size());
}



