#include "Log.hh"

#include <fstream>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/atomic.hpp>

namespace oe
{

void Log::init(const std::string& log_cfg)
{
  static boost::atomic<int> ref(0);

  if( ++ref>1 )
  {
    --ref;
    return ;
  }
  
  namespace logging = boost::log;
  namespace attrs = boost::log::attributes;

  // logging::register_simple_formatter_factory< CThostFtdcReqUserLoginField, char >("CThostFtdcReqUserLoginField");
  
  // logging::register_simple_formatter_factory< severity_level, char >("Severity");
  // logging::register_simple_filter_factory< severity_level, char >("Severity");


  std::ifstream settings(log_cfg.data());
  
  if (!settings.is_open())
  {
    throw std::runtime_error("Could not open log config file: " + log_cfg);
  }

  // Read the settings and initialize logging library
  logging::init_from_stream(settings);

  // Add some attributes

  logging::add_common_attributes();

  // logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

  logging::core::get()->add_global_attribute("Scope", attrs::named_scope());

  logging::core::get()->add_global_attribute("Uptime", attrs::timer());
}

};  // namespace oe
