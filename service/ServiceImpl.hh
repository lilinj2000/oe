#ifndef OE_SERVICE_IMPL_HH_
#define OE_SERVICE_IMPL_HH_

#include <string>
#include <memory>

#include "interface/Service.hh"
#include "Config.hh"

namespace oe
{

class ETFManager;
class TxOptixPolicy;

class ServiceImpl : public Service
{
 public:
  ServiceImpl();

  virtual void fetchCommodityTradingScheduleList(CommodityTradingScheduleList& theCTSList);
  
  virtual ~ServiceImpl();

 private:

  OEServiceCfg cfg_;

  std::auto_ptr<ETFManager> etf_manager_;
  std::auto_ptr<TxOptixPolicy> txoptix_policy_;
};
  
} // namespace oe

#endif // OE_SERVICE_IMPL_HH_
