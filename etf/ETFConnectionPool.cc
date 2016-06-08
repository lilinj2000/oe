
#include "ETFConnectionPool.hh"

#include <unistd.h>

namespace oe
{

ETFConnectionPool::ETFConnectionPool(const std::string& dbhost, const std::string& user, const std::string& password, const std::string& db):
	conns_in_use_(0),
	dbhost_(dbhost),
	user_(user),
	password_(password),
	db_(db)
	{
	}

ETFConnectionPool::~ETFConnectionPool()
{
  clear();
}

mysqlpp::Connection* ETFConnectionPool::grab()
{
  while (conns_in_use_ > 8) {
    // std::cout.put('R'); std::cout.flush(); // indicate waiting for release
    sleep(1);
  }

  ++conns_in_use_;
  return mysqlpp::ConnectionPool::grab();
}

void ETFConnectionPool::release(const mysqlpp::Connection* pc)
{
  mysqlpp::ConnectionPool::release(pc);
  --conns_in_use_;
}

mysqlpp::Connection* ETFConnectionPool::create()
{
  // Create connection using the parameters we were passed upon
  // creation.  This could be something much more complex, but for
  // the purposes of the example, this suffices.
  // std::cout.put('C'); std::cout.flush(); // indicate connection creation
  return new mysqlpp::Connection(
      db_.empty() ? 0 : db_.c_str(),
      dbhost_.empty() ? 0 : dbhost_.c_str(),
      user_.empty() ? 0 : user_.c_str(),
      password_.empty() ? "" : password_.c_str());
}

void ETFConnectionPool::destroy(mysqlpp::Connection* cp)
{
  // Our superclass can't know how we created the Connection, so
  // it delegates destruction to us, to be safe.
  std::cout.put('D'); std::cout.flush(); // indicate connection destruction
  delete cp;
}

unsigned int ETFConnectionPool::max_idle_time()
{
  // Set our idle time at an example-friendly 3 seconds.  A real
  // pool would return some fraction of the server's connection
  // idle timeout instead.
  return 3;
}

} // namespace oe
