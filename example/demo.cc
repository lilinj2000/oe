#include "Service.hh"

#include <iostream>

int main()
{
  try
  {
    oe::Service* service = oe::Service::create();

    oe::CommodityTradingScheduleList theCTSList;
    service->fetchCommodityTradingScheduleList(theCTSList);

  }
  catch(std::exception& e)
  {
    std::cout <<"exception catched: " <<e.what() <<std::endl;
    return -1;
  }
  
  std::cout <<"Success!!!" <<std::endl;
  
  return 0;
}
