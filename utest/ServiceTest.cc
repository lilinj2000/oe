#include <string>
#include <memory>

#include "interface/Service.hh"
#include "UtilsTest.hh"
#include "gtest/gtest.h"

namespace oe
{

TEST(ServiceTest, testFetchCommodityTradingScheduleList)
{
  std::auto_ptr<Service> service( Service::create() );

  ASSERT_TRUE( NULL != service.get() );

  oe::CommodityTradingScheduleList theCTSList;
  service->fetchCommodityTradingScheduleList(theCTSList);

  std::auto_ptr<oe::UtilsTest> utils(new oe::UtilsTest());
  utils->outputCTSList(theCTSList);

  EXPECT_TRUE( 15==theCTSList.size() );
}

}
