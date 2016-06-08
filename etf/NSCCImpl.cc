#include "NSCCImpl.hh"


namespace oe
{

NSCCImpl::NSCCImpl():
    tbl_("ETF.NSCCHIST")
{
}

NSCCImpl::~NSCCImpl()
{
}

void NSCCImpl::fetchCUInfoToday(mysqlpp::Connection& conn, CUInfo& theCU)
{
  std::string condition = "date(DATE)=curdate()";
  fetchCUInfo(conn, theCU, condition);
}
  
void NSCCImpl::fetchCUInfoLastWorkDay(mysqlpp::Connection& conn, CUInfo& theCU)
{
  std::string queryString = "select distinct date(DATE) from " + tbl_;
  queryString += " where DATE<curdate() order by DATE desc limit 1;";

  std::string lastWorkDay;
  try
  {
    mysqlpp::Query query = conn.query(queryString.data());

    if (mysqlpp::StoreQueryResult res = query.store())
    {
      mysqlpp::StoreQueryResult::const_iterator it;
      for (it = res.begin(); it != res.end(); ++it)
      {
        mysqlpp::Row row = *it;

        lastWorkDay = row[0].c_str();
      }
    }
  }
  catch (mysqlpp::Exception& e)
  {
    std::cerr << "Failed to query the last work day: " <<
        e.what() << std::endl;

    throw;
  }

  std::string condition = "date(DATE)=date('" + lastWorkDay + "')";
  fetchCUInfo(conn, theCU, condition);
}

void NSCCImpl::fetchCUInfo(mysqlpp::Connection& conn, CUInfo& theCU, const std::string& theCondition)
{
  std::string queryString = "select COMPONENT, SHARES, DATE from " + tbl_;
  queryString += " where " + theCondition;

  // std::cout <<"fetchCUInfo: " <<queryString <<std::endl;
  
  try
  {
    mysqlpp::Query query = conn.query(queryString.data());

    if (mysqlpp::StoreQueryResult res = query.store())
    {

      mysqlpp::StoreQueryResult::const_iterator it;
      for (it = res.begin(); it != res.end(); ++it)
      {
        mysqlpp::Row row = *it;
        Ticker aTicker;
        aTicker.commodity_ = row[0].c_str();

        if( aTicker.commodity_=="CASH" )
          continue;  // ignore the CASH
        
        aTicker.quantity_ = row[1];
        aTicker.date_ = row[2].c_str();

        theCU.push_back(aTicker);
      }
    }
  }
  catch (mysqlpp::Exception& e)
  {
    std::cerr << "Failed to query cu info: " <<
        e.what() << std::endl;

    throw;
  }
  
}

}  // namespace oe
