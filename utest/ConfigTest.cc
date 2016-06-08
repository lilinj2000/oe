#include <memory>

#include "service/Config.hh"
#include "gtest/gtest.h"

namespace oe
{

class ConfigTest : public ::testing::Test
{
public:

  void SetUp()
  {
  }

protected:

};

TEST_F(ConfigTest, oeConfigTest)
{
  Config cfg;

  const OEServiceCfg& oe_cfg = cfg.oeServiceCfg();

  ASSERT_EQ( oe_cfg.dbhost_, "localhost" );
  ASSERT_EQ( oe_cfg.dbuser_, "test" );
  ASSERT_EQ( oe_cfg.dbpassword_, "test" );
  ASSERT_EQ( oe_cfg.dbname_, "testdb" );
  ASSERT_EQ( oe_cfg.logcfg_, "./log.cfg" );
}

}  // namespace oe
