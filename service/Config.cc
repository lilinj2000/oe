#include "Config.hh"

#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>

namespace oe
{

Config::Config(int argc, const char* argv[])
{
  namespace po = boost::program_options;
  std::string config_file;
  
  // the options will be allowed only on command line
  po::options_description cmdline_options("Command line options");
  cmdline_options.add_options()
      ("version,v", "print version string")
      ("help", "produce help message")
      ("config,c", po::value<std::string>(&config_file)->default_value("oe.cfg"),
       "name of a file of a configuration.")
      ;

  // the options will be allowed only on config file
  po::options_description oe_config("OEService");
  oe_config.add_options()
      ("OEService.db_host", po::value<std::string>(&oe_service_cfg_.dbhost_), 
       "db host")
      ("OEService.db_user", po::value<std::string>(&oe_service_cfg_.dbuser_), 
       "db user")
      ("OEService.db_password", po::value<std::string>(&oe_service_cfg_.dbpassword_), 
       "db password")
      ("OEService.db_name", po::value<std::string>(&oe_service_cfg_.dbname_), 
       "db name")
      ("OEService.log_cfg", po::value<std::string>(&oe_service_cfg_.logcfg_), 
       "log config file name")
      ;

  po::options_description config_file_options;
  config_file_options.add(oe_config);

  // parse command line
  po::variables_map vm;
  store(po::parse_command_line(argc, argv, cmdline_options), vm);
  notify(vm);

  if (vm.count("help")) 
  {
    std::cout << cmdline_options;
    return;
  }

  std::ifstream ifs(config_file.c_str());
  if (!ifs)
  {
    throw std::runtime_error("can not open config file: " + config_file);
  }
  else
  {
    store(parse_config_file(ifs, config_file_options), vm);
    notify(vm);
  }

  return;
}

Config::~Config()
{
}

};  // namespace oe
