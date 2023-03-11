#include "DBs.hpp"

using namespace nl;
using namespace a3c;

DBs::DBs()
{

  std::string path("./resources/dictionary/labels_geo.csv");

  // 別途新しくファイルを開く
  nl::FileAccessor fa(path);
  // fa.getFiletype()
  fa.readFileSync();
  fa.getMemoryBank();
  // LABELS_GEO_TABLE.readCSV();
}
