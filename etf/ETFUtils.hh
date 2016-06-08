#ifndef OE_ETF_UTILS_HH_
#define OE_ETF_UTILS_HH_

#include "ETFManager.hh"
#include "CRInterface.hh"
#include "NSCCInterface.hh"

namespace oe
{
class ETFUtils
{
 public:
  ETFUtils();

  virtual ~ETFUtils();

  void toTradingInfo(const CUInfo& theCUInfo, TradingInfo& theTradingInfo);

  // curTrading - preTrading
  void mergeTradingInfo(const TradingInfo& curTrading, const TradingInfo& preTrading, TradingInfo& realTrading);

  void calFinalTradingInfo(const TradingInfo& curTrading, const CRInfoList& crInfoList, TradingInfo& realTradingInfo);

  void outputTradingInfo(const TradingInfo& theTradingInfo);
  
 private:
  unsigned long dummy_shares_;
};

};     // namespace oe

#endif  // OE_ETF_UTILS_HH_
