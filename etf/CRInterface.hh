#ifndef OE_CR_INTERFACE_HH_
#define OE_CR_INTERFACE_HH_

#include <string>
#include <vector>

#include <mysql++.h>

#include "ETFDef.hh"

namespace oe
{

class CRInterface
{
 public:

  virtual ~CRInterface() {};

  virtual void fetchCRInfoList(mysqlpp::Connection& conn, CRInfoList& theCRInfoList) = 0;
  
 private:

};
  
} // namespace oe

#endif // OE_CR_INTERFACE_HH_
