#ifndef OE_VOLUMEDAILY_INTERFACE_HH_
#define OE_VOLUMEDAILY_INTERFACE_HH_

#include <string>
#include <vector>

#include <mysql++.h>

#include "ETFDef.hh"

namespace oe
{

class VolumeDailyInterface
{
 public:

  virtual ~VolumeDailyInterface() {};

  virtual void fetchTickerVolumeInfo(mysqlpp::Connection& conn, TradingInfo& theTradingInfo) = 0;
  
 private:

};
  
} // namespace oe

#endif // OE_VOLUMEDAILY_INTERFACE_HH_
