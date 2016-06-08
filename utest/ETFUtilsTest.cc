#include <memory>

#include "etf/ETFUtils.hh"
#include "gtest/gtest.h"


class ETFUtilsTest : public ::testing::Test
{
public:

  void SetUp()
  {
    utils_.reset(new oe::ETFUtils());
  }

protected:

  std::auto_ptr<oe::ETFUtils> utils_;
};



TEST_F(ETFUtilsTest, testToTradingInfo)
{

  // =====================CU=================
  //     cu1506  3       2015-04-10 15:55:47
  //     rb1510  15      2015-04-10 15:55:47
  //     y1509   7       2015-04-10 15:55:47
  //     au1506  1       2015-04-10 15:55:47
  //     SR509   6       2015-04-10 15:55:47
  //     j1505   1       2015-04-10 15:55:47
  //     j1509   2       2015-04-10 15:55:47
  //     =====================CU END==============

  oe::CUInfo theCUInfo;

  oe::Ticker aTicker;
  aTicker.commodity_ = "cu1506";
  aTicker.quantity_ = 3;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "rb1510";
  aTicker.quantity_ = 15;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "y1509";
  aTicker.quantity_ = 7;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "au1506";
  aTicker.quantity_ = 1;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "SR509";
  aTicker.quantity_ = 6;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "j1505";
  aTicker.quantity_ = 1;
  theCUInfo.push_back(aTicker);

  aTicker.commodity_ = "j1509";
  aTicker.quantity_ = 2;
  theCUInfo.push_back(aTicker);

    
  oe::TradingInfo theTradingInfo;
  utils_->toTradingInfo(theCUInfo, theTradingInfo);

  utils_->outputTradingInfo(theTradingInfo);

  EXPECT_TRUE( 7==theTradingInfo.size() );
  
}

TEST_F(ETFUtilsTest, testMergeTradingInfo)
{
  // =====================CU=================
  //     cu1506  3       2015-04-10 15:55:47
  //     rb1510  15      2015-04-10 15:55:47
  //     y1509   7       2015-04-10 15:55:47
  //     au1506  1       2015-04-10 15:55:47
  //     SR509   6       2015-04-10 15:55:47
  //     j1505   1       2015-04-10 15:55:47
  //     j1509   2       2015-04-10 15:55:47
  //     =====================CU END==============

  // =====================CU=================
  //     cu1506  3       2015-04-09 16:24:00
  //     rb1510  15      2015-04-09 16:24:00
  //     y1509   7       2015-04-09 16:24:00
  //     au1506  1       2015-04-09 16:24:00
  //     SR509   6       2015-04-09 16:24:00
  //     j1505   2       2015-04-09 16:24:00
  //     j1509   1       2015-04-09 16:24:00
  //     =====================CU END==============

  oe::TickerInfo tickerInfo;

  oe::TradingInfo curTrading;
  tickerInfo.quantity_ = 3;
  curTrading["cu1506"] = tickerInfo;
  tickerInfo.quantity_ = 15;
  curTrading["rb1510"] = tickerInfo;
  tickerInfo.quantity_ = 7;
  curTrading["y1509"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  curTrading["au1506"] = tickerInfo;
  tickerInfo.quantity_ = 6;
  curTrading["SR509"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  curTrading["j1505"] = tickerInfo;
  tickerInfo.quantity_ = 2;
  curTrading["j1509"] = tickerInfo;


  oe::TradingInfo preTrading;
  tickerInfo.quantity_ = 3;
  preTrading["cu1506"] = tickerInfo;
  tickerInfo.quantity_ = 15;
  preTrading["rb1510"] = tickerInfo;
  tickerInfo.quantity_ = 7;
  preTrading["y1509"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  preTrading["au1506"] = tickerInfo;
  tickerInfo.quantity_ = 6;
  preTrading["SR509"] = tickerInfo;
  tickerInfo.quantity_ = 2;
  preTrading["j1505"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  preTrading["j1509"] = tickerInfo;

  oe::TradingInfo realTrading;
  utils_->mergeTradingInfo(curTrading, preTrading, realTrading);

  utils_->outputTradingInfo(realTrading);

  EXPECT_TRUE(2==realTrading.size());
}

TEST_F(ETFUtilsTest, testCalFinalTradingInfo)
{
  // =====================CU=================
  //     cu1506  3       2015-04-10 15:55:47
  //     rb1510  15      2015-04-10 15:55:47
  //     y1509   7       2015-04-10 15:55:47
  //     au1506  1       2015-04-10 15:55:47
  //     SR509   6       2015-04-10 15:55:47
  //     j1505   1       2015-04-10 15:55:47
  //     j1509   2       2015-04-10 15:55:47
  //     =====================CU END==============

  // =====================CRInfo List=================
  //     100     1       2015-04-10 16:48:38
  //     =====================CRInfo List END==============
  oe::TickerInfo tickerInfo;

  oe::TradingInfo curTrading;
  tickerInfo.quantity_ = 3;
  curTrading["cu1506"] = tickerInfo;
  tickerInfo.quantity_ = 15;
  curTrading["rb1510"] = tickerInfo;
  tickerInfo.quantity_ = 7;
  curTrading["y1509"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  curTrading["au1506"] = tickerInfo;
  tickerInfo.quantity_ = 6;
  curTrading["SR509"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  curTrading["j1505"] = tickerInfo;
  tickerInfo.quantity_ = 2;
  curTrading["j1509"] = tickerInfo;

  // =====================TradinfInfo=================
  //                          j1505   -1
  //                          j1509   1
  // =====================TradingInfo END==============
  oe::TradingInfo realTrading;
  tickerInfo.quantity_ = -1;
  realTrading["j1505"] = tickerInfo;
  tickerInfo.quantity_ = 1;
  realTrading["j1509"] = tickerInfo;
  
  oe::CRInfoList crInfoList;
  oe::CRInfo aCRInfo;
  aCRInfo.shares_ = 100;
  aCRInfo.is_creation_ = 1;
  crInfoList.push_back(aCRInfo);

  utils_->calFinalTradingInfo(curTrading, crInfoList, realTrading);

  utils_->outputTradingInfo(realTrading);

  EXPECT_TRUE(7==realTrading.size());
}


