#ifndef OE_SERVICE_HH_
#define OE_SERVICE_HH_

#include <string>
#include <vector>

namespace oe
{

//////////////////////////////////////////////////////
// Schedule: start/end time pair
//////////////////////////////////////////////////////
typedef struct
{
  unsigned long start_; // start time, the unit is second, in terms of seconds elapsed since 00:00 AM. (e.g, 09:00 AM will be 9*3600 = 32400) 
  unsigned long end_; // end time, the unit is second, in terms of seconds elapsed since 00:00 AM. (e.g, 09:00 AM will be 9*3600 = 32400)
} Schedule;

//////////////////////////////////////////////////////
// Trading 
// contains one single ticker, quantity pair
//////////////////////////////////////////////////////
typedef struct
{
  std::string commodity_;  // commodity trading code (j1506, SR509, etc.)
  long long quantity_; // commodity trading quantity (in units of of shares)
}Trading;

typedef std::vector<Trading> TradingList;



//////////////////////////////////////////////////////
// CommodityTradingSchedule
// the primary data structure for what and how much
// is to be traded during a certain time period.
//
// time period start/end is given by startTime() endTime()
// tradingList() returns a vector containing ticker/quantity pair
// the vector contains all tickers to be traded in the time period
/////////////////////////////////////////////////////
class CommodityTradingSchedule
{
 public:
  CommodityTradingSchedule();
  ~CommodityTradingSchedule();

  unsigned long startTime() const;
  unsigned long endTime() const;

  const TradingList& tradingList() const;

  void startTime(unsigned long start);
  void endTime(unsigned long end);

  void pushTrading(const Trading& trade);
  
 private:
  Schedule schedule_;  // commodity trading schedule
  TradingList tradings_;  // commodity trading list
};


//////////////////////////////////////////////////////
// the list containing CommodityTradingSchedule for the
// whole day. in the order of trading time
/////////////////////////////////////////////////////
typedef std::vector<CommodityTradingSchedule> CommodityTradingScheduleList;


class Service
{
 public:
  virtual ~Service() {}

  virtual void fetchCommodityTradingScheduleList(CommodityTradingScheduleList& theCTSList) = 0;
  
  static Service* create();
  
};
  
} // namespace oe

#endif // OE_SERVICE_HH_
