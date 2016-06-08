#include "ServiceImpl.hh"
#include "Log.hh"
#include "etf/ETFManager.hh"
#include "strategy/TxOptixPolicy.hh"

namespace oe
{

CommodityTradingSchedule::CommodityTradingSchedule()
{
  schedule_.start_ = 0;
  schedule_.end_ = 0;
}

CommodityTradingSchedule::~CommodityTradingSchedule()
{
}

unsigned long CommodityTradingSchedule::startTime() const
{
  return schedule_.start_;
}

unsigned long CommodityTradingSchedule::endTime() const
{
  return schedule_.end_;
}

const TradingList& CommodityTradingSchedule::tradingList() const
{
  return tradings_;
}

void CommodityTradingSchedule::startTime(unsigned long start)
{
  schedule_.start_ = start;
}

void CommodityTradingSchedule::endTime(unsigned long end)
{
  schedule_.end_ = end;
}

void CommodityTradingSchedule::pushTrading(const Trading& trade)
{
  tradings_.push_back(trade);
}

ServiceImpl::ServiceImpl()
{
  Config cfg;
  cfg_ = cfg.oeServiceCfg();

  OE_LOG_INIT( cfg_.logcfg_ );

  etf_manager_.reset(new ETFManager(cfg_.dbhost_, cfg_.dbuser_, cfg_.dbpassword_, cfg_.dbname_));
  
}

ServiceImpl::~ServiceImpl()
{
  OE_TRACE <<"ServiceImpl::~ServiceImpl()";
}

void ServiceImpl::fetchCommodityTradingScheduleList(CommodityTradingScheduleList& theCTSList)
{
  OE_TRACE <<"ServiceImpl::fetchCommodityTradingScheduleList()";
    
  theCTSList.clear();

  // fetch the trading info
  TradingInfo tradingInfo;
  etf_manager_->fetchTradingInfo(tradingInfo);

  // construct the TxOptix input
  oe::TxOptions options;
  options.og_path_ = "out.xml";
  options.run_mode_ = oe::TX_RUN_SINGLE;
  options.debug_exist_ = true;
  options.debug_ = 1;

  TradingInfo::const_iterator i_iter = tradingInfo.begin();
  int seq = 0;
  oe::InstrsInfo instrs_info;
  for(; i_iter!=tradingInfo.end(); i_iter++)
  {
    oe::Instrument instr;
    instr.seq_ = seq++;
    instr.symbol_ = i_iter->first;
    instr.alpha_ = 0.5;
    instr.beta_ = 0.5;
    instr.gamma_ = 2.0;
    instr.zeta_ = 0.2;
    instr.tis_ = 0.5;
    instr.ris_ = 0.5;
    instr.pis_ = 0.5;
    instr.volume_ = 2765338;
    instr.vol_ = 1.0;
    instr.price_ = 4193.000;
    instr.quantity_ = i_iter->second.quantity_;

    const VolatilityInfoList& volatility = i_iter->second.volatility_info_;
    VolatilityInfoList::const_iterator i_volatility = volatility.begin();
    for(; i_volatility!=volatility.end(); i_volatility++)
    {
      oe::Tuple tuple;
      tuple.time_ = i_volatility->at_;
      tuple.value_ = i_volatility->volatility_;

      instr.volatility_profile_.push_back(tuple);
    }

    const VolumeInfoList& volume = i_iter->second.volume_info_;
    VolumeInfoList::const_iterator i_volume = volume.begin();
    for(; i_volume!=volume.end(); i_volume++)
    {
      oe::Tuple tuple;
      tuple.time_ = i_volume->at_;
      tuple.value_ = i_volume->volume_;

      instr.volume_profile_.push_back(tuple);
    }

    instrs_info.instr_list_.push_back(instr);
  }

  for(int i=1; i<=9; i++)
  {
    instrs_info.schedule_list_.push_back(i/10.0);
  }

  txoptix_policy_->execute(options, instrs_info, theCTSList);
  
  return ;
}

Service* Service::create()
{
  return new ServiceImpl();
}

} // namespace oe
