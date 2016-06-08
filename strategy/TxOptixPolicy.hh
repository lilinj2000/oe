#ifndef OE_TX_OPTIX_POLICY_HH_
#define OE_TX_OPTIX_POLICY_HH_

#include <string>
#include <vector>

#include "TxOptimizer2.h"
#include "interface/Service.hh"

namespace oe
{

typedef enum 
{
  TX_RUN_NOTHING,
  TX_RUN_SINGLE,
  TX_RUN_STAGED,
  TX_COST_ONLY
}TxRunMode;

struct TxOptions
{
  // Optimal Trading Schedule command line arguments
  // ===============================================
  // -ic    [file path] 'for input xml files
  std::string ic_path_;
  
  // -og    [file path] 'for output xml files
  std::string og_path_;
  
  // -alpha [0.0, 1.0)  'c/l/o/w for all alphas for each instrument
  double alpha_;
  bool alpha_exist_;

  // -beta  [0.0,    )  'c/l/o/w for beta for each instrument from xml
  double beta_;
  bool beta_exist_;
  
  // -gamma [1.5, 2.5]  'c/l/o/w for gamma default 2.0
  double gamma_;
  bool gamma_exist_;
  
  // -lambd [0.0,    )  'c/l/o/w for price of risk for all instrument
  double lambda_;
  bool lambda_exist_;
  
  // -ti    [0.0,    )  'c/l/o/w for temporary impact scaling
  double ti_;
  bool ti_exist_;
  
  // -pi    [0.0,    )  'c/l/o/w for permanent impact scaling
  double pi_;
  bool pi_exist_;
  
  // -multi [-int,int]  'c/l/o/w for quantity/share multiplier
  double multi_;
  bool multi_exist_;
  
  // -rate  [0.0, 1.0]  'c/l/o/w for decay exponent or 1/e time for exp
  double rate_;
  double rate_exist_;
  
  // -calc  [ task ] 
  // -single            'single xml file processing 
  // -phases { # burst per phase } 'phased optimization 
  // -cost   { comma-separated strategy for each burst }
  TxRunMode run_mode_;
  std::vector<double> vars_;
  int spaghetti_;
  
  // -falsify'Turn off booleanco
  bool disable_booleanco_;
  
  // -vf'Turn on simple volume fraction. default: adjusted fraction
  bool enable_volume_;
  
  // -xd'Turn on exponential decay. default: power law decay
  bool enable_decay_;
  
  // -yes  [ almgren ] 'turn on almgren
  bool enable_almgren_;
  
  // -yes  [ cap {%peaklmt}  ]     'turn on burst %adv cap
  bool enable_cap_;
  double cap_;
  bool cap_exist_;
  
  // -yes  [ preempt {%contrast} ] 'turn on front-nonempty vs max peak
  bool enable_preempt_;
  double preempt_;
  bool preempt_exist_;
  
  // -yes  [ incl_pi ] 'to use permanent impact in derivative calcs
  bool enable_incl_;
  
  // -yes  [ tempo {out-of-synch penalty} ]
  bool enable_tempo_;
  double penalty_;
  bool penalty_exist_;
  
  // -ze   { # reptition } 'for the timing of above two 
  int reptition_;
  bool reptition_exist_;
  
  // debug info
  int debug_;
  bool debug_exist_;

  bool enable_usd_;
  bool enable_uad_;

  TxOptions();
  
};

typedef struct
{
  double time_;
  double value_;
}Tuple;

typedef std::vector<Tuple> TupleList;

typedef struct
{
  int seq_;
  std::string symbol_;
  double alpha_;
  double beta_;
  double gamma_;
  double zeta_;
  double tis_;
  double ris_;
  double pis_;
  double volume_;
  double vol_;
  double price_;
  double quantity_;

  TupleList volatility_profile_;
  TupleList volume_profile_;
  
}Instrument;

typedef std::vector<Instrument> InstrumentList;

typedef std::vector<double> TxScheduleList;

typedef struct
{
  InstrumentList instr_list_;
  TxScheduleList schedule_list_;
}InstrsInfo;

class TxOptixPolicy
{
 public:
  
  TxOptixPolicy();
  virtual ~TxOptixPolicy();

  void execute(const TxOptions& options, const InstrsInfo& instrs_info, CommodityTradingScheduleList& theCTSList);

 private:

  void initialContext(TxOS::txOptimizerCtx_t ctx, const TxOptions& options);
  
  void initialContext(const InstrsInfo& instrs_info,
                      TxOS::txOptimizerCtx_t ctx, 
                      std::vector<double>& schedule,
                      std::vector<TxOS::TxCostFunctional>& instr_manifest,
                      std::map<std::string, HxNumerix::SeriesStineman>& profile_volume,
                      std::map<std::string, HxNumerix::SeriesPolinear<0, 2> >& profile_volatility,
                      HxNumerix::Matrix<double>& instr_covarix,
                      std::map<int, std::string>& factor_manifest,
                      HxNumerix::Matrix<double>& factor_exposure,
                      HxNumerix::Matrix<double>& factor_covarix);

  void toCTSList(const std::vector<TxOS::TxCostFunctional>& instr_manifest,
                 const TxScheduleList&  theTxSchedule,
                 const TxOS::txOptimizerOutput_s& output,
                 CommodityTradingScheduleList& theCTSList);

  unsigned long scheduleTime(double time_rate, bool is_stop);

};

}  // namespace oe


#endif // OE_TX_OPTIX_POLICY_HH_
