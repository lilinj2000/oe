#ifndef OE_VOLATILITYDAILY_IMPL_HH_
#define OE_VOLATILITYDAILY_IMPL_HH_

#include "VolatilityDailyInterface.hh"

#include <vector>
#include <string>

namespace oe
{
  
class VolatilityDailyImpl : public VolatilityDailyInterface
{
 public:
  VolatilityDailyImpl();

  virtual void fetchTickerVolatilityInfo(mysqlpp::Connection& conn, TradingInfo& theTradingInfo);
  
  virtual ~VolatilityDailyImpl();

 protected:

 private:
  const std::string tbl_;
};
  
} // namespace oe

#endif // OE_DAILYUSE_IMPL_HH_
