#include "interface/Service.hh"

#include <stdio.h>
#include <iostream>

std::string timeString(unsigned long second)
{
  char szTime[1024];
  snprintf(szTime, 1024, "%lu:%02lu", second/3600, (second%3600)/60);

  return szTime;
      
}

void outputCTSList(const oe::CommodityTradingScheduleList& theCTSList)
{
  fprintf(stdout, "\n=====================CTSList=================\n");
  oe::CommodityTradingScheduleList::const_iterator i_iter = theCTSList.begin();
  for(; i_iter!=theCTSList.end(); i_iter++)
  {
    fprintf(stdout, "schedule(%lu - %lu) === (%s - %s)\n",
            i_iter->startTime(), i_iter->endTime(),
            timeString(i_iter->startTime()).c_str(), timeString(i_iter->endTime()).c_str());

    const oe::TradingList& tradings = i_iter->tradingList();
    oe::TradingList::const_iterator i_trade = tradings.begin();

    for(; i_trade!=tradings.end(); i_trade++)
    {
      fprintf(stdout, " (commodity: %s, quantity: %lu)", i_trade->commodity_.c_str(), i_trade->quantity_);
    }

    fprintf(stdout, "\n");
  }

  fprintf(stdout, "=====================CTSList END==============\n");
}

int main()
{
  try
  {
    oe::Service* service = oe::Service::create();

    oe::CommodityTradingScheduleList theCTSList;
    service->fetchCommodityTradingScheduleList(theCTSList);
    
    outputCTSList(theCTSList);
  }
  catch(std::exception& e)
  {
    std::cout <<"exception catched: " <<e.what() <<std::endl;
    return -1;
  }
  

  return 0;
}
