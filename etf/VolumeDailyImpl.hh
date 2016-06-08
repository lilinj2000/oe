#ifndef OE_VOLUMEDAILY_IMPL_HH_
#define OE_VOLUMEDAILY_IMPL_HH_

#include "VolumeDailyInterface.hh"

#include <vector>
#include <string>

namespace oe
{
  
class VolumeDailyImpl : public VolumeDailyInterface
{
 public:
  VolumeDailyImpl();

  virtual void fetchTickerVolumeInfo(mysqlpp::Connection& conn, TradingInfo& theTradingInfo);
  
  virtual ~VolumeDailyImpl();

 protected:

 private:
  const std::string tbl_;
};
  
} // namespace oe

#endif // OE_DAILYUSE_IMPL_HH_
