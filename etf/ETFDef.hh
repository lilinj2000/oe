#ifndef ETF_DEF_HH_
#define ETF_DEF_HH_

#include <string>
#include <map>
#include <vector>

namespace oe
{

// CR info
typedef struct
{
  unsigned long shares_;
  int is_creation_;
  std::string request_time_;
} CRInfo;

typedef std::vector<CRInfo> CRInfoList;

// CU info
typedef struct
{
  std::string commodity_;
  unsigned long quantity_;
  std::string date_;
}Ticker;

typedef std::vector<Ticker> CUInfo;

// Volume info
typedef struct
{
  double at_;
  double volume_;
} VolumeInfo;

typedef std::vector<VolumeInfo> VolumeInfoList;

// volatility info
typedef struct
{
  double at_;
  double volatility_;
} VolatilityInfo;

typedef std::vector<VolatilityInfo> VolatilityInfoList;

// Ticker list
typedef std::vector<std::string> TickerList;

typedef struct
{
  long long quantity_;  // quantity per ticker
  VolumeInfoList volume_info_;  // volume info
  VolatilityInfoList volatility_info_;  // volatility info
}TickerInfo;

typedef std::map<std::string, TickerInfo> TradingInfo;

};  // namespace oe

#endif
