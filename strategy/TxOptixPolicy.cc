#include <cstdio>
#include <vector>
#include <map>
#include <memory>

#include "TxOptixPolicy.hh"



namespace oe
{

TxOptions::TxOptions():
    alpha_(0),
    alpha_exist_(false),
    beta_(0),
    beta_exist_(false),
    gamma_(0),
    gamma_exist_(false),
    lambda_(0),
    lambda_exist_(false),
    ti_(0),
    ti_exist_(false),
    pi_(0),
    pi_exist_(false),
    multi_(0),
    multi_exist_(false),
    rate_(0),
    rate_exist_(false),
    run_mode_(TX_RUN_NOTHING),
    spaghetti_(0),
    disable_booleanco_(false),
    enable_volume_(false),
    enable_decay_(false),
    enable_almgren_(false),
    enable_cap_(false),
    cap_(0),
  cap_exist_(false),
  enable_preempt_(false),
  preempt_(0),
  preempt_exist_(false),
  enable_incl_(false),
  enable_tempo_(false),
  penalty_(0),
  penalty_exist_(false),
  reptition_(0),
  reptition_exist_(false),
  debug_(0),
  debug_exist_(false),
  enable_usd_(false),
  enable_uad_(false)
{
}

void TxOptixPolicy::initialContext(TxOS::txOptimizerCtx_t ctx, const TxOptions& options)
{
    // ctx->ic_path = options.ic_path_;
  ctx->og_path = options.og_path_;

  if( options.alpha_exist_ )
  {
    ctx->opts.alpha = options.alpha_;
    ctx->opts.individual = false;
  }

  if( options.beta_exist_ )
  {
    ctx->opts.beta = options.beta_;
    ctx->opts.individual = false;
  }

  if( options.gamma_exist_ )
  {
    ctx->opts.gamme = options.gamma_;
    ctx->opts.individual = false;
  }

  if( options.lambda_exist_ )
  {
    ctx->opts.lambda = options.lambda_;
    ctx->opts.individual = false;
  }

  if( options.ti_exist_ )
  {
    ctx->opts.ti_scale = options.ti_;
    ctx->opts.individual = false;
  }

  if( options.pi_exist_ )
  {
    ctx->opts.pi_scale = options.pi_;
    ctx->opts.individual = false;
  }

  if( options.multi_exist_ )
  {
    ctx->opts.multiplier = options.multi_;
    ctx->opts.leverage = true;
    ctx->opts.individual = false;
  }

  if( options.rate_exist_ )
  {
    ctx->opts.decay = options.rate_;
    ctx->opts.individual = false;
  }

  if( options.run_mode_==TX_COST_ONLY )
  {
    ctx->vars = options.vars_;
  }

  if( options.run_mode_==TX_RUN_STAGED )
  {
    ctx->opts.spaghetti = options.spaghetti_;
  }

  if( options.disable_booleanco_ )
  {
    ctx->opts.booleanco = false;
  }
  
  if( options.enable_volume_ )
  {
    ctx->vi = TxOS::eViStraight;
  }

  if( options.enable_decay_ )
  {
    ctx->di = TxOS::eDecayEXP;
  }

  if( options.enable_almgren_ )
  {
    ctx->opts.almgren = true;
  }

  if( options.enable_cap_ )
  {
    ctx->opts.peakcap = true;
    
    if( options.cap_exist_ )
    {
      ctx->opts.peaklmt = options.cap_;
    }
  }

  if( options.enable_preempt_ )
  {
    ctx->opts.preemptive = true;
    
    if( options.preempt_exist_ )
    {
      ctx->opts.preload = options.preempt_;
    }
  }

  if( options.enable_incl_ )
  {
    ctx->opts.pi_incl = true;
  }

  if( options.enable_tempo_ )
  {
    ctx->opts.tempo = true;

    if( options.penalty_exist_ )
    {
      ctx->opts.penalty = options.penalty_;
    }
  }

  if( options.reptition_exist_ )
  {
    ctx->opts.reptition = options.reptition_;
  }

  if( options.debug_exist_ )
  {
    ctx->opts.debug = options.debug_;
  }

  if( options.enable_usd_ )
  {
    ctx->opts.usd = true;

    if( options.enable_uad_ )
    {
      ctx->opts.uad = true;
    }
    else
    {
      ctx->opts.uad = false;
    }
  }
  
}

void TxOptixPolicy::initialContext(const InstrsInfo& instrs_info,
                      TxOS::txOptimizerCtx_t ctx, 
                      std::vector<double>& schedule,
                      std::vector<TxOS::TxCostFunctional>& instr_manifest,
                      std::map<std::string, HxNumerix::SeriesStineman>& profile_volume,
                      std::map<std::string, HxNumerix::SeriesPolinear<0, 2> >& profile_volatility,
                      HxNumerix::Matrix<double>& instr_covarix,
                      std::map<int, std::string>& factor_manifest,
                      HxNumerix::Matrix<double>& factor_exposure,
                      HxNumerix::Matrix<double>& factor_covarix)
{
  const InstrumentList& instrs = instrs_info.instr_list_;

  // clear
  schedule.clear();
  instr_manifest.clear();
  profile_volume.clear();
  profile_volatility.clear();

  instr_covarix.resize(0, 0, 0.0);
  factor_manifest.clear();
  factor_exposure.resize(0, 0, 0.0);
  factor_covarix.resize(0, 0, 0.0);

  // initial schedule
  std::copy(instrs_info.schedule_list_.begin(), instrs_info.schedule_list_.end(), std::back_inserter(schedule));
  std::sort(schedule.begin(), schedule.end(), std::less<double>());
  
  // initial instr_manifest
  int seq = 0;
  InstrumentList::const_iterator i_iter = instrs.begin();
  for( ; i_iter!=instrs.end(); i_iter++ )
  {
    TxOS::TxCostFunctional cost;
    
    // seq
    cost.seq( i_iter->seq_ );
    // symbol
    cost.ticker( i_iter->symbol_ );
    // alpha
    cost.alpha( i_iter->alpha_ );
    // beta
    cost.beta( i_iter->beta_ );
    // gamma
    cost.gamma( i_iter->gamma_ );
    // zeta
    cost.decay( i_iter->zeta_ );
    // ris
    cost.lambda( i_iter->ris_ );
    // pis
    cost.pi_scale( i_iter->pis_ );
    // tis
    cost.ti_scale( i_iter->tis_ );
    // volume
    cost.volume( i_iter->volume_ );
    // vol
    cost.vol( i_iter->vol_ );
    // price
    cost.price( i_iter->price_ );
    // quantity
    cost.share( i_iter->quantity_ );

    if (false == ctx->opts.individual)
    {
      if (ctx->opts.alpha >= 0.0 && ctx->opts.alpha < 1.0)
        cost.alpha(ctx->opts.alpha);
      if (ctx->opts.beta >= 0.0)
        cost.beta(ctx->opts.beta);
      if (ctx->opts.gamme >= 0.0)
        cost.gamma(ctx->opts.gamme);
      if (ctx->opts.decay >= 0.0 && ctx->opts.gamme < 1.0)
        cost.decay(ctx->opts.decay);
      if (ctx->opts.lambda >= 0.0)
        cost.lambda(ctx->opts.lambda);
      if (ctx->opts.ti_scale > 0.0)
        cost.ti_scale(ctx->opts.ti_scale);
      if (ctx->opts.pi_scale > 0.0)
        cost.pi_scale(ctx->opts.pi_scale);
      if (ctx->opts.leverage)
        cost.share(cost.share() * ctx->opts.multiplier);
    }
    
    if (cost.ticker().empty())
    {
      char sid[12] ;
      sprintf(sid, "instr.%05d", seq);
      cost.ticker(sid);
    }
    if (cost.seq() < 0)
      cost.seq(seq);

    seq++;
    
    instr_manifest.push_back(cost);

    // initial volume_profile
    {
      HxNumerix::TimeValTuple tuple;
      HxNumerix::SeriesStineman volco;

      const TupleList& volume_profile = i_iter->volume_profile_;
      
      for(unsigned i=0; i<volume_profile.size(); i++)
      {
        tuple[TqCO::Time] = volume_profile[i].time_;
        tuple[TqCO::Value] = volume_profile[i].value_;

        volco.push_back(tuple);
      }

      std::sort(volco.begin(), volco.end(), HxNumerix::LessThan<TqCO::Time, HxNumerix::TimeValTuple>());
      profile_volume.insert(std::map<std::string, HxNumerix::SeriesStineman>::value_type(cost.ticker(), volco));
    }

    // initial volatility_profile
    {
      HxNumerix::TimeValTuple tuple;
      HxNumerix::SeriesPolinear<0, 2> volco;

      const TupleList& volatility_profile = i_iter->volatility_profile_;
      
      for(unsigned i=0; i<volatility_profile.size(); i++)
      {
        tuple[TqCO::Time] = volatility_profile[i].time_;
        tuple[TqCO::Value] = volatility_profile[i].value_;

        volco.push_back(tuple);
      }

      std::sort(volco.begin(), volco.end(), HxNumerix::LessThan<TqCO::Time, HxNumerix::TimeValTuple>());
      profile_volatility.insert(std::map<std::string, HxNumerix::SeriesPolinear<0, 2> >::value_type(cost.ticker(), volco));
    }

  }

  if (instr_covarix.row() != instr_manifest.size()
      || instr_covarix.col() != instr_manifest.size())
  {
    instr_covarix.resize(instr_manifest.size(), instr_manifest.size(), 0.0);
    instr_covarix.diagonalize(1.0);
  }

}

static void outputTxOptimizer(const TxOS::txOptimizerOutput_s& result)
{
  std::cout <<"=============txOptimizerOutput_s===============" <<std::endl;
  std::cout <<"cost_final: " <<result.cost_final <<std::endl;
  std::cout <<"ti_charge: " <<result.ti_charge <<std::endl;
  std::cout <<"pi_charge: " <<result.pi_charge <<std::endl;
  std::cout <<"ri_charge: " <<result.ri_charge <<std::endl;
  std::cout <<"xi_stress: " <<result.xi_stress <<std::endl;
  std::cout <<"ti_initial: " <<result.ti_initial <<std::endl;
  std::cout <<"pi_initial: " <<result.pi_initial <<std::endl;
  std::cout <<"ri_initial: " <<result.ri_initial <<std::endl;
  std::cout <<"xi_initial: " <<result.xi_initial <<std::endl;

  std::cout <<"optisch is:" <<std::endl;
  std::cout <<result.optisch <<std::endl;

  std::cout <<"ti_costs is:" <<std::endl;
  std::cout <<result.ti_costs <<std::endl;
  
  std::cout <<"pi_costs is:" <<std::endl;
  std::cout <<result.pi_costs <<std::endl;

  std::cout <<"ri_costs is:" <<std::endl;
  std::cout <<result.ri_costs <<std::endl;
  
  std::cout <<"=============txOptimizerOutput_s end===========" <<std::endl;
}
                              
TxOptixPolicy::TxOptixPolicy()
{
}

TxOptixPolicy::~TxOptixPolicy()
{
}

void TxOptixPolicy::execute(const TxOptions& options, const InstrsInfo& instrs_info, CommodityTradingScheduleList& theCTSList)
{
  TxOS::txOptimizerOptions_s opts;
  
  std::auto_ptr<TxOS::txOptimizerCtx_s> ctx( TxOS::createOptimizerContext(&opts) );   // this should probably be released

  initialContext(ctx.get(), options);

  std::vector<TxOS::TxCostFunctional> instr_manifest;
  std::vector<double> schedule;
  std::map<std::string, HxNumerix::SeriesPolinear<0, 2> > profile_volatility;
  std::map<std::string, HxNumerix::SeriesStineman> profile_volume;
  std::map<int, std::string> factor_manifest;
  HxNumerix::Matrix<double> factor_exposure;
  HxNumerix::Matrix<double> factor_covarix;
  HxNumerix::Matrix<double> instr_covarix;
  HxNumerix::Matrix<int>    trade_history(0,0,0.0);
  TxOS::txOptimizerOutput_s output;

  initialContext(instrs_info, ctx.get(), schedule, instr_manifest, profile_volume, profile_volatility, instr_covarix, factor_manifest, factor_exposure, factor_covarix);

  std::cout <<"===============instr_manifest===========" <<std::endl;
  std::copy(instr_manifest.begin(), instr_manifest.end(), std::ostream_iterator<TxOS::TxCostFunctional>(std::cout, "\n"));
  std::cout <<"===============instr_manifest end=======" <<std::endl;

  std::cout <<"===============schedule===========" <<std::endl;
  std::copy(schedule.begin(), schedule.end(), std::ostream_iterator<double>(std::cout, " "));
  std::cout <<"\n===============schedule end=======" <<std::endl;

  try
  {
    switch ( options.run_mode_ )
    {
      case TX_RUN_SINGLE:
        TxOS::run_single(ctx.get(), &output, trade_history, schedule, instr_manifest, profile_volatility, profile_volume, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
        log_parameters(ctx.get(), instr_manifest, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
      
        break;
      
      case TX_RUN_STAGED:
        TxOS::run_staged(ctx.get(), &output, trade_history, schedule, instr_manifest, profile_volatility, profile_volume, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
        log_parameters(ctx.get(), instr_manifest, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
      
        break;
      
      case TX_COST_ONLY:
        TxOS::calc_cost (ctx.get(), schedule, instr_manifest, profile_volatility, profile_volume, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
        log_parameters(ctx.get(), instr_manifest, factor_manifest, factor_exposure, factor_covarix, instr_covarix);
      
        break;
      
      case TX_RUN_NOTHING:
        std::cout<<"Run mode is eRunNothing. Not scheduling."<<std::endl;

    }
  }
  catch(std::exception& e)
  {
    std::cerr <<"exception catched: " <<e.what() <<std::endl;
  }
  catch( ... )
  {
    std::cerr <<"unknown exception catched." <<std::endl;

    std::cerr <<"err: " <<ctx->err <<std::endl;
    std::cerr <<"debug_info: " <<ctx->debug_info <<std::endl;
  }

  outputTxOptimizer(output);

  std::cout <<"========trade_history=======" <<std::endl;
  std::cout <<trade_history <<std::endl;
  std::cout <<"========trade_history end===" <<std::endl;

  toCTSList(instr_manifest, schedule, output, theCTSList);
  
}

void TxOptixPolicy::toCTSList(const std::vector<TxOS::TxCostFunctional>& instr_manifest,
                 const TxScheduleList&  theTxSchedule,
                 const TxOS::txOptimizerOutput_s& output,
                 CommodityTradingScheduleList& theCTSList)
{
    std::map<int, std::string> tickers;
    for(unsigned int i=0; i<instr_manifest.size(); i++)
    {
      tickers[instr_manifest[i].seq()] = instr_manifest[i].ticker();
    }


    int row=0;
    TxScheduleList::const_iterator i_iter = theTxSchedule.begin();
    for(; i_iter!=theTxSchedule.end(); )
    {
      // begin time
      double time_b = *i_iter;
      
      ++i_iter;
      if( i_iter==theTxSchedule.end() )
        continue;

      // end time
      double time_e = *i_iter;

      CommodityTradingSchedule cts;
      cts.startTime( scheduleTime(time_b, false) );
      cts.endTime( scheduleTime(time_e, true) );
      
      int col = 0;
      std::map<int, std::string>::iterator i_map = tickers.begin();
      for( ; i_map!=tickers.end(); i_map++)
      {
        Trading aTrade;
        aTrade.commodity_ = i_map->second;
        aTrade.quantity_ = output.optisch[row][col++];

        cts.pushTrading( aTrade );
        
        // std::cout <<" (" <<i_map->second <<", " <<output.optisch[row][col++] <<")";
      }
      // std::cout <<std::endl;

      theCTSList.push_back(cts);
      
      row++;
    }
}

unsigned long TxOptixPolicy::scheduleTime(double time_rate, bool is_stop)
{
  // 9:00-10:15; 10:30-11:30; 13:30-15:00
  unsigned long point0 = 9*60*60;  // 9:00
  unsigned long point1 = point0 + 90*60; // 10:30
  unsigned long point2 = point1 + 180*60;  // 13:30
  
  unsigned long period = 75+60+90;
  unsigned long period1 = 75;
  unsigned long period2 = 60;
  unsigned long period3 = 90;

  unsigned long time_m = time_rate*period + 0.5;
  unsigned long time_r = 0;
  
  if( time_m<period1 )
  {
    time_r = point0 + time_m*60;
  }
  else if( time_m<(period1+period2) )
  {
    if( is_stop && time_m==period1)
    {
      time_r = point0 + period1*60;
    }
    else
    {
      time_r = point1 + (time_m-period1)*60;
    }
  }
  else
  {
    if( is_stop && time_m==(period1+period2) )
    {
      time_r = point1 + period2*60;
    }
    else
    {
      time_r = point2 + (time_m-period1-period2)*60;
    }
  }

  return time_r;
}

}  // namespace oe
