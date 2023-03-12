#include "DBs.hpp"

using namespace nl;
using namespace a3c;
using namespace std::string_literals;

DBs::DBs()
{
  initialized = false;
  dbdataPath = "./resources/dbdata/";
}

bool DBs::init()
{
  Logger logger;
  if (initialized)
  {
    // 初期化済み
    logger.infoLog("DBs::init() already initialized.");
    return false;
  }

  {
    // LABELS_GEO データ読み込み
    std::string path(dbdataPath + "labels_geo.csv");
    FileAccessor fa(path);
    if (fa.readFileSync() == false)
    {
      logger.errorLog("DBs::init() Could'nt read labels_geo.csv");
    }
    std::string csvData = fa.getMemoryBank()->readStringToEnd();
    CSVReader csvReader(',', '\\');
    csvReader.readCsv(csvData);
    int count = TABLE_LABELS_GEO.readCSV(csvReader);
    logger.infoLog("DBs::init():TABLE_LABELS_GEO csv to DB loaded. count="s + std::to_string(count) + "."s);
  }
  return true;
}
