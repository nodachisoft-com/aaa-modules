#include "TerrainGeoLabelGenerator.hpp"

using namespace a3c;
using namespace nl;
using namespace std::string_literals;

bool TerrainGeoLabelGenerator::init(const int randomSeed, DBs &_dbRef)
{

  dbRef = &_dbRef;

  // === 植生 (BIOME) ラベル初期化 ===
  BiomeMeadowLabelList = getLabelsStartWith(BIOME_MEADOW_LABEL_STARTWITH);     // 草原
  BiomeDesertLabelList = getLabelsStartWith(BIOME_DESERT_LABEL_STARTWITH);     // 砂漠
  BiomeForestLabelList = getLabelsStartWith(BIOME_FOREST_LABEL_STARTWITH);     // 森林
  BiomeMountainLabelList = getLabelsStartWith(BIOME_MOUNTAIN_LABEL_STARTWITH); // 山岳
  BiomePoisonLabelList = getLabelsStartWith(BIOME_POISON_LABEL_STARTWITH);     // 汚染地帯
  BiomeSeaLabelList = getLabelsStartWith(BIOME_SEA_LABEL_STARTWITH);           // 海
  BiomeSeashoreLabelList = getLabelsStartWith(BIOME_SEASHORE_LABEL_STARTWITH); // 海岸
  BiomeSnowLabelList = getLabelsStartWith(BIOME_SNOW_LABEL_STARTWITH);         // 雪

  // === 大きさ (SCALE) ラベル ===
  ScaleSmallLabelList = getLabelsStartWith(SCALESMALL_LABEL_STARTWITH); // 小さい
  ScaleLargeLabelList = getLabelsStartWith(SCALELARGE_LABEL_STARTWITH); // 大きい

  // === ユニーク (UNIQUE) ラベル初期化 ===
  UniqueLabelList = getLabelsStartWith(UNIQUE_LABEL_STARTWITH); // ユニーク

  return true;
}

std::string TerrainGeoLabelGenerator::generateLabel(const Biome &biome)
{
  MtRandomizer rnd(randomSeed + biome.biomeNo);

  std::string labelScale("");
  if (biome.biomeAreaSize < 60) // サイズ（小）
  {
    labelScale = getRndFromVecLabel(ScaleSmallLabelList, rnd).EN;
  }
  else if (biome.biomeAreaSize < 100) // サイズ（中）は特になし
  {
  }
  else // サイズ（大）
  {
    labelScale = getRndFromVecLabel(ScaleLargeLabelList, rnd).EN;
  }
  // ユニークなラベルを取得
  std::string labelUnique = fetchRndFromVecLabel(UniqueLabelList, rnd).EN;

  std::string label = labelScale + " " + labelUnique;
  return label;
}
