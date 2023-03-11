#include "DBs.hpp"

using namespace nl;
using namespace a3c;

DBs::DBs()
{
  initialized = false;
  dbdataPath = "./resources/dbdata/";
}

bool DBs::init()
{
  if (initialized)
  {
    // 初期化済み
    Logger logger;
    logger.infoLog("DBs::init() already initialized.");
    return false;
  }

  {
    // LABELS_GEO データ読み込み
    std::string path(dbdataPath + "labels_geo.csv");
    FileAccessor fa(path);
    if (fa.readFileSync() == false)
    {
      Logger logger;
      logger.errorLog("DBs::init() Could'nt read labels_geo.csv");
    }
    std::string csvData = fa.getMemoryBank()->readStringToEnd();
    CSVReader csvReader(',', '\\');
    csvReader.readCsv(csvData);
    TABLE_LABELS_GEO.readCSV(csvReader);
  }
  return true;
}
