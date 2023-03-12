#include "TerrainGeoLabelGenerator.hpp"

using namespace a3c;
using namespace nl;
using namespace std::string_literals;

bool TerrainGeoLabelGenerator::init(const int randomSeed, DBs &_dbRef)
{
  rnd = MtRandomizer(randomSeed);
  dbRef = &_dbRef;
  return true;
}

std::string TerrainGeoLabelGenerator::generateLabel(const Biome &biome)
{

  std::vector<a3c::LabelsGeoEntity> ScaleSmallLabelList = dbRef->TABLE_LABELS_GEO.selectStartWithByPK("Scale_Small_");
  int scaleLabelIndex = rnd.getRndInt(0, ScaleSmallLabelList.size() - 1);
  std::cout << "generateBiomeLabel labelIndexRange=" << scaleLabelIndex << std::endl;
  std::string labelScale = ScaleSmallLabelList.at(scaleLabelIndex).EN;
  std::string label = labelScale + " Place"s;
  std::cout << "generateBiomeLabel_label=" << label << std::endl;
  return label;
}
