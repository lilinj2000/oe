#ifndef OE_ETF_CONNECTION_POOL_HH_
#define OE_ETF_CONNECTION_POOL_HH_

#include <string>
#include <mysql++.h>

namespace oe
{
  
class ETFConnectionPool : public mysqlpp::ConnectionPool
{
 public:
  ETFConnectionPool(const std::string& dbhost, const std::string& user, const std::string& passwd, const std::string& db);

  mysqlpp::Connection* grab();

  void release(const mysqlpp::Connection* pc);
  
  virtual ~ETFConnectionPool();

 protected:
  mysqlpp::Connection* create();
  
  void destroy(mysqlpp::Connection* cp);

  unsigned int max_idle_time();
  
 private:
  std::string dbhost_;
  std::string user_;
  std::string password_;
  std::string db_;

  unsigned int conns_in_use_;
  
};
  
} // namespace oe

#endif // OE_ETF_CONNECTION_POOL_HH_
