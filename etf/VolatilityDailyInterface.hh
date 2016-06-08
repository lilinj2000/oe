#ifndef OE_VOLATILITYDAILY_INTERFACE_HH_
#define OE_VOLATILITYDAILY_INTERFACE_HH_

#include <string>
#include <vector>

#include <mysql++.h>

#include "ETFDef.hh"

namespace oe
{

class VolatilityDailyInterface
{
 public:

  virtual ~VolatilityDailyInterface() {};

  virtual void fetchTickerVolatilityInfo(mysqlpp::Connection& conn, TradingInfo& theTradingInfo) = 0;
  
 private:

};
  
} // namespace oe

#endif // OE_VOLATILITYDAILY_INTERFACE_HH_
