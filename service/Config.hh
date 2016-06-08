#ifndef OE_CONFIG_HH_
#define OE_CONFIG_HH_

#include <string>

namespace oe
{

typedef struct
{
  std::string dbhost_;
  std::string dbuser_;
  std::string dbpassword_;
  std::string dbname_;
  std::string logcfg_;
}OEServiceCfg;

class Config
{
 public:
  
  Config(int argc=0, const char* argv[]=NULL);
  ~Config();

  const OEServiceCfg& oeServiceCfg() const
  {
    return oe_service_cfg_;
  }

 private:
  OEServiceCfg oe_service_cfg_;
};

}  // namespace oe


#endif // OE_CONFIG_HH_
