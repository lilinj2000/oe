#include <stdlib.h>
#include <string>
#include <memory>

#include "mysql++.h"
#include "gtest/gtest.h"

#include "etf/NSCCImpl.hh"

class NSCCImplTest : public ::testing::Test
{
 public:

  void SetUp()
  {
    conn_.reset(new mysqlpp::Connection("ETF", "localhost", "test", "test"));
    nscc_.reset(new oe::NSCCImpl());

    // prepareData();
  }

 protected:

  void prepareData()
  {
    if( system("mysql -utest -ptest ETF < NSCCHIST.sql")<0 )
    {
      std::cerr <<"load NSCCHIST failed." <<std::endl;
      exit(-1);
    }
  

    mysqlpp::Query query = conn_->query();

    query <<"update NSCCHIST set DATE=now() where date(DATE)=date('2015-04-08')";
    mysqlpp::SimpleResult res = query.execute();

    query.reset();
    query <<"update NSCCHIST set DATE=now() - INTERVAL 1 DAY where date(DATE)=date('2015-04-07')";
    res = query.execute();
  
  }

  std::auto_ptr<mysqlpp::Connection> conn_;
  std::auto_ptr<oe::NSCCImpl> nscc_;

};

static void outputCUInfo(const oe::CUInfo& theCU)
{
  fprintf(stdout, "\n=====================CU=================\n");
  oe::CUInfo::const_iterator i_iter = theCU.begin();
  for(; i_iter!=theCU.end(); i_iter++)
  {
    std::cout <<i_iter->commodity_ <<"\t"
              <<i_iter->quantity_ <<"\t"
              <<i_iter->date_ <<std::endl;
  }

  fprintf(stdout, "=====================CU END==============\n");
}



TEST_F(NSCCImplTest, testFetchCUInfoToday)
{
  oe::CUInfo theCU;
  
  nscc_->fetchCUInfoToday(*conn_, theCU);

  outputCUInfo(theCU);
  
  EXPECT_TRUE(7==theCU.size());
}

TEST_F(NSCCImplTest, testFetchCUInfoLastWorkDay)
{
  oe::CUInfo theCU;
  
  nscc_->fetchCUInfoLastWorkDay(*conn_, theCU);

  outputCUInfo(theCU);
  
  EXPECT_TRUE(7==theCU.size());
}



