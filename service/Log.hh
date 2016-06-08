#ifndef OE_LOG_HH_
#define OE_LOG_HH_


#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/from_stream.hpp>


namespace oe
{
namespace src = boost::log::sources;
namespace attrs = boost::log::attributes;

// Here we define our application severity levels.
enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal,
    pdu
};

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
    {
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "fatal",
        "pdu"
    };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}

//  Global logger declaration
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(log_, src::severity_logger_mt< >)

class Log
{
 public:
  static void init(const std::string& log_cfg="log.cfg");

 private:
};


}  // namespace oe

#define OE_LOG_INIT(x) oe::Log::init(x)

#define OE_LOG(x) BOOST_LOG_SEV(oe::log_::get(), x) <<"(" __FILE__ <<":" <<__LINE__ <<") "

#define OE_TRACE OE_LOG(oe::trace)
#define OE_DEBUG OE_LOG(oe::debug)
#define OE_INFO OE_LOG(oe::info)
#define OE_WARNING OE_LOG(oe::warning)
#define OE_ERROR OE_LOG(oe::error)
#define OE_FATAL OE_LOG(oe::fatal)
#define OE_PDU OE_LOG(oe::pdu)


#endif // OE_LOG_HH_
