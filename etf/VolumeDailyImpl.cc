#include "VolumeDailyImpl.hh"

namespace oe
{

VolumeDailyImpl::VolumeDailyImpl():
    tbl_("ETF.volume_daily")
{
}

VolumeDailyImpl::~VolumeDailyImpl()
{
}

void VolumeDailyImpl::fetchTickerVolumeInfo(mysqlpp::Connection& conn, TradingInfo& theTradingInfo)
{
  TradingInfo::iterator i_iter = theTradingInfo.begin();
  for(; i_iter!=theTradingInfo.end(); i_iter++)
  {
    // f1 = seconds - seconds(at 9:00)
    // to minute : f2 = f1/60
    // to rate : f2/225
    std::string time_change = "(time_to_sec(time) - time_to_sec('9:00'))/60/225 as time";
    
    std::string queryString = "select " + time_change + ", volume from " + tbl_;
    queryString += " where instrument_id='" + i_iter->first + "' and date=curdate()";
    queryString += " order by time asc";

    try
    {
      VolumeInfoList volumeList;
      
      mysqlpp::Query query = conn.query(queryString.data());

      if (mysqlpp::StoreQueryResult res = query.store())
      {
        mysqlpp::StoreQueryResult::const_iterator it;
        for (it = res.begin(); it != res.end(); ++it)
        {
          mysqlpp::Row row = *it;
          
          VolumeInfo aVolumeInfo;
          memset(&aVolumeInfo, 0x0, sizeof(aVolumeInfo));
          
          aVolumeInfo.at_ = row[0];
          
          if( !row[1].is_null() )
            aVolumeInfo.volume_ = row[1] ;
          
          volumeList.push_back( aVolumeInfo );
        }
      }

      i_iter->second.volume_info_ = volumeList;
    }
    catch (mysqlpp::Exception& e)
    {
      std::cerr << "Failed to query volume daily info: " <<
          e.what() << std::endl;

      throw;
    }
  }  // end for
  
}

}  // namespace oe
