#include "CRImpl.hh"

namespace oe
{

CRImpl::CRImpl():
    tbl_("ETF.cr_requests_2")
{
}

CRImpl::~CRImpl()
{
}

void CRImpl::fetchCRInfoList(mysqlpp::Connection& conn, CRInfoList& theCRInfoList)
{
  std::string queryString = "select shares, IsCreation, RequestTime from " + tbl_;
  queryString += " where date(RequestTime)=curdate()";

  try
  {
    mysqlpp::Query query = conn.query(queryString.data());

    if (mysqlpp::StoreQueryResult res = query.store())
    {

      mysqlpp::StoreQueryResult::const_iterator it;
      for (it = res.begin(); it != res.end(); ++it)
      {
        mysqlpp::Row row = *it;
        CRInfo aCRInfo;
        aCRInfo.shares_ = row[0];
        aCRInfo.is_creation_ = row[1];
        aCRInfo.request_time_ = row[2].c_str();

        theCRInfoList.push_back(aCRInfo);
      }
    }
  }
  catch (mysqlpp::Exception& e)
  {
    std::cerr << "Failed to query cr info: " <<
        e.what() << std::endl;

    throw;
  }
  
}

}  // namespace oe
