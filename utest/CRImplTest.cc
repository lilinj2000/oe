
#include <stdlib.h>
#include <string>
#include <memory>

#include "mysql++.h"
#include "gtest/gtest.h"

#include "etf/CRImpl.hh"


class CRImplTest : public ::testing::Test
{
 public:
  void SetUp()
  {
    conn_.reset(new mysqlpp::Connection("ETF", "localhost", "test", "test"));
    cr_.reset(new oe::CRImpl());

    prepareData();
  }

  
 protected:
  void prepareData()
  {
      if( system("mysql -utest -ptest ETF < cr_requests_2.sql")<0 )
      {
        std::cerr <<"load cr_requests_2 failed." <<std::endl;
        exit(-1);
      }

      mysqlpp::Query query = conn_->query();

      query <<"update cr_requests_2 set RequestTime=now()";
      mysqlpp::SimpleResult res = query.execute();

  }
  
  std::auto_ptr<mysqlpp::Connection> conn_;
  std::auto_ptr<oe::CRImpl> cr_;
  
};


static void outputCRInfoList(const oe::CRInfoList& theCRInfoList)
{
  fprintf(stdout, "\n=====================CRInfo List=================\n");
  oe::CRInfoList::const_iterator i_iter = theCRInfoList.begin();
  for(; i_iter!=theCRInfoList.end(); i_iter++)
  {
    std::cout <<i_iter->shares_ <<"\t"
              <<i_iter->is_creation_ <<"\t"
              <<i_iter->request_time_ <<std::endl;
  }

  fprintf(stdout, "=====================CRInfo List END==============\n");
}


TEST_F(CRImplTest, testFetchCRInfoList)
{
  oe::CRInfoList theCRInfoList;
  
  cr_->fetchCRInfoList(*conn_, theCRInfoList);

  outputCRInfoList(theCRInfoList);
  
  EXPECT_TRUE(1==theCRInfoList.size());
}



