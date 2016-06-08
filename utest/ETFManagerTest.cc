#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "etf/ETFManager.hh"
#include "etf/ETFUtils.hh"

class ETFManagerTest : public ::testing::Test
{
 public:
  void SetUp()
  {
    std::string dbhost = "localhost";
    std::string user = "test";
    std::string password = "test";
    std::string db = "ETF";

    etf_manager_.reset(new oe::ETFManager(dbhost, user, password, db));
    utils_.reset(new oe::ETFUtils());
  }

 protected:
  std::auto_ptr<oe::ETFManager> etf_manager_;  
  std::auto_ptr<oe::ETFUtils> utils_;
};

TEST_F(ETFManagerTest, testFetchTradingInfo)
{

  oe::TradingInfo theTradingInfo;
  etf_manager_->fetchTradingInfo(theTradingInfo);

  utils_->outputTradingInfo(theTradingInfo);

  EXPECT_TRUE(7==theTradingInfo.size());
  
}




