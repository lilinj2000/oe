#ifndef OE_ETF_MANAGER_HH_
#define OE_ETF_MANAGER_HH_

#include <memory>

#include "ETFDef.hh"

namespace oe
{

class ETFConnectionPool;
class CRInterface;
class NSCCInterface;
class VolumeDailyInterface;
class VolatilityDailyInterface;

class ETFUtils;

class ETFManager
{
 public:
  ETFManager(const std::string& dbhost, const std::string& user, const std::string& passwd, const std::string& db);

  void fetchTradingInfo(TradingInfo& theTradingInfo);
  
  virtual ~ETFManager();

 protected:

  std::auto_ptr<ETFConnectionPool> conn_pool_;
  std::auto_ptr<CRInterface> cr_;
  std::auto_ptr<NSCCInterface> nscc_;
  std::auto_ptr<VolumeDailyInterface> volumedaily_;
  std::auto_ptr<VolatilityDailyInterface> volatilitydaily_;
  
  std::auto_ptr<ETFUtils> utils_;
};
  
} // namespace oe

#endif // OE_ETF_MANAGER_HH_
