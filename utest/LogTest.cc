#include <memory>

#include "service/Log.hh"
#include "gtest/gtest.h"

namespace oe
{

class LogTest : public ::testing::Test
{
public:

  LogTest()
  {
    OE_LOG_INIT();
  }
  
  void SetUp()
  {
  }

protected:

};

TEST_F(LogTest, logTest)
{
  OE_TRACE <<"this is the trace log";
  OE_DEBUG <<"this is the debug log";
  OE_INFO <<"this is the info log";
  OE_WARNING <<"this is the warning log";
  OE_ERROR <<"this is the error log";
  OE_FATAL <<"this is the fatal log";
}

}  // namespace oe
