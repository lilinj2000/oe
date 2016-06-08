#ifndef OE_NSCC_INTERFACE_HH_
#define OE_NSCC_INTERFACE_HH_

#include <string>
#include <vector>

#include <mysql++.h>

#include "ETFDef.hh"

namespace oe
{

class NSCCInterface
{
 public:

  virtual void fetchCUInfoToday(mysqlpp::Connection& conn, CUInfo& theCU) = 0;
  
  virtual void fetchCUInfoLastWorkDay(mysqlpp::Connection& conn, CUInfo& theCU) = 0;
  
  virtual ~NSCCInterface() {};

 private:


};
  
} // namespace oe

#endif // OE_NSCC_INTERFACE_HH_
