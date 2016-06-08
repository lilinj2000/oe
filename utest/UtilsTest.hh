#include <string>

#include "interface/Service.hh"

#ifndef UTILS_TEST_HH_
#define UTILS_TEST_HH_

namespace oe
{

class UtilsTest
{
 public:
  
  std::string timeString(unsigned long second);

  void outputCTSList(const oe::CommodityTradingScheduleList& theCTSList);
};

}  // end namespace oe


#endif






