#ifndef OE_CR_IMPL_HH_
#define OE_CR_IMPL_HH_

#include "CRInterface.hh"

namespace oe
{
  
class CRImpl : public CRInterface
{
 public:
  CRImpl();

  virtual void fetchCRInfoList(mysqlpp::Connection& conn, CRInfoList& theCRInfoList) ;

  virtual ~CRImpl();

 private:
  const std::string tbl_;
};
  
} // namespace oe

#endif // OE_NSCC_IMPL_HH_
