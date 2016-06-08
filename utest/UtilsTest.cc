#include <stdio.h>
#include "UtilsTest.hh"

namespace oe
{

std::string UtilsTest::timeString(unsigned long second)
{
  char szTime[1024];
  snprintf(szTime, 1024, "%lu:%02lu", second/3600, (second%3600)/60);

  return szTime;
      
}

void UtilsTest::outputCTSList(const oe::CommodityTradingScheduleList& theCTSList)
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
      fprintf(stdout, " (commodity: %s, quantity: %ld)", i_trade->commodity_.c_str(), i_trade->quantity_);
    }

    fprintf(stdout, "\n");
  }

  fprintf(stdout, "=====================CTSList END==============\n");
}

}  // end namespace oe

