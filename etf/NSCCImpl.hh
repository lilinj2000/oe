#ifndef OE_NSCC_IMPL_HH_
#define OE_NSCC_IMPL_HH_

#include "NSCCInterface.hh"

namespace oe
{
  
class NSCCImpl : public NSCCInterface
{
 public:
  NSCCImpl();

  virtual void fetchCUInfoToday(mysqlpp::Connection& conn, CUInfo& theCUList);
  
  virtual void fetchCUInfoLastWorkDay(mysqlpp::Connection& conn, CUInfo& theCUList);

  virtual ~NSCCImpl();

 private:

  void fetchCUInfo(mysqlpp::Connection& conn, CUInfo& theCU, const std::string& theCondition);


  const std::string tbl_;
};
  
} // namespace oe

#endif // OE_NSCC_IMPL_HH_
