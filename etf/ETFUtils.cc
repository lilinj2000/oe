#include "ETFUtils.hh"

#include <stdexcept>
#include <cstdio>

namespace oe
{

ETFUtils::ETFUtils():
    dummy_shares_(10000)
{
}

ETFUtils::~ETFUtils()
{
}

void ETFUtils::toTradingInfo(const CUInfo& theCUInfo, TradingInfo& theTradingInfo)
{
  theTradingInfo.clear();

  CUInfo::const_iterator i_iter = theCUInfo.begin();
  for(; i_iter!=theCUInfo.end(); i_iter++)
  {
    std::string commodity = i_iter->commodity_;
    unsigned long quantity = i_iter->quantity_;

    if( theTradingInfo.count(commodity)>0 )
    {
      throw std::invalid_argument("duplicated commodity found on one certain cu, the data fault.");
    }

    TickerInfo tickerInfo;
    tickerInfo.quantity_ = quantity;
    theTradingInfo[commodity] = tickerInfo;
  }
}

void ETFUtils::mergeTradingInfo(const TradingInfo& curTrading, const TradingInfo& preTrading, TradingInfo& realTrading)
{
  TradingInfo preTmpTrading = preTrading;
  
  // step1 process the cur trading info
  TradingInfo::const_iterator i_iter = curTrading.begin();
  for(; i_iter!=curTrading.end(); i_iter++)
  {
    std::string commodity = i_iter->first;
    
    TradingInfo::const_iterator i_pre = preTrading.find(commodity);
    if( i_pre!=preTrading.end() )
    {

      long long result = i_iter->second.quantity_ - i_pre->second.quantity_;

      if( result!=0 )
      {
        TickerInfo tickerInfo;
        tickerInfo.quantity_ = result;
        realTrading[commodity] = tickerInfo;
      }
      
      preTmpTrading.erase(commodity);
    }
    else
      realTrading[commodity] = i_iter->second;
  }

  // step2 process the left pre trading info
  TradingInfo::const_iterator i_left = preTmpTrading.begin();
  for(; i_left!=preTmpTrading.end(); i_left++)
  {
    long long result = -1 * i_left->second.quantity_;
    TickerInfo tickerInfo;
    tickerInfo.quantity_ = result;
    
    realTrading[i_left->first] = tickerInfo;
  }

  return ;
}

void ETFUtils::calFinalTradingInfo(const TradingInfo& curTrading, const CRInfoList& crInfoList, TradingInfo& realTradingInfo)
{
  // realTradingInfo * shares
  TradingInfo::iterator i_iter = realTradingInfo.begin();
  for( ; i_iter!=realTradingInfo.end(); i_iter++ )
  {
    i_iter->second.quantity_ *= dummy_shares_;
  }

  long long shares = 0;
  CRInfoList::const_iterator i_cr = crInfoList.begin();
  for( ; i_cr!=crInfoList.end(); i_cr++ )
  {
    if(i_cr->is_creation_==1 )
      shares += i_cr->shares_;
    else
      shares -= i_cr->shares_;
  }

  // process the shares
  if( shares!=0 )
  {
    TradingInfo::const_iterator i_iter = curTrading.begin();
    for(; i_iter!=curTrading.end(); i_iter++)
    {
      realTradingInfo[i_iter->first].quantity_ += shares*i_iter->second.quantity_;
    }
  }
}

void ETFUtils::outputTradingInfo(const oe::TradingInfo& theTradingInfo)
{
  fprintf(stdout, "\n=====================TradingInfo=================\n");
  oe::TradingInfo::const_iterator i_iter = theTradingInfo.begin();
  for(; i_iter!=theTradingInfo.end(); i_iter++)
  {
    std::cout <<i_iter->first <<":" <<std::endl;
    std::cout <<"quantity: " <<i_iter->second.quantity_ <<std::endl;
    std::cout <<"volume info:" <<std::endl;
    oe::VolumeInfoList::const_iterator i_volume = i_iter->second.volume_info_.begin();
    for(; i_volume!=i_iter->second.volume_info_.end(); i_volume++)
    {
      std::cout  <<i_volume->at_ <<"\t" <<i_volume->volume_ <<std::endl;
    }
    std::cout <<"volatility info:" <<std::endl;
    oe::VolatilityInfoList::const_iterator i_volatility = i_iter->second.volatility_info_.begin();
    for(; i_volatility!=i_iter->second.volatility_info_.end(); i_volatility++)
    {
      std::cout  <<i_volatility->at_ <<"\t" <<i_volatility->volatility_ <<std::endl;
    }
    
  }

  fprintf(stdout, "=====================TradingInfo END==============\n");
}

}
