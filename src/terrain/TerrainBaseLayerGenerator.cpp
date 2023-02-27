#include "TerrainBaseLayerGenerator.hpp"

using namespace a3c;
using namespace nl;

TerrainBaseLayerGenerator::TerrainBaseLayerGenerator()
{
}

TerrainBaseLayerGenerator::~TerrainBaseLayerGenerator()
{
}

void TerrainBaseLayerGenerator::generateBaseTerrain()
{
  // Continents/Biom などの基本的な地理情報を 1024 x 1024 で生成し勢力図、経路情報の生成に使用する
  Size2d resSize = conf.getStrategyResolutionSize();
  int width = resSize.x;
  int height = resSize.y;

  // HeightField 作成
  strategyMapHF.init(resSize.x, resSize.y, 0.0f);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float res = getLayerHfAsWorldmapchip_StrategyLevel(
          u * conf.MapUnitChipSize,
          v * conf.MapUnitChipSize);

      strategyMapHF.setWithIgnoreOutOfRangeData(u, v, res);
    }
  }

  // 地層（Stratum）定義
  int STRATUM_DEEPSEA = 0;      // 深海
  int STRATUM_SEA = 1;          // 浅瀬
  int STRATUM_SEASHORE = 2;     // 海岸の砂浜
  int STRATUM_PLAIN = 3;        // 様々なバイオームが存在する領域
  int STRATUM_MOUNTAIN = 4;     // 山岳
  int STRATUM_SNOWMOUNTAIN = 5; // 高山（雪）
  std::vector<float> stratumLv{
      100.0f,
      120.0f,
      124.0f,
      140.0f,
      200.0f,
      999.0f};

  // Biome 定義
  int BIOME_DEEPSEA = 0;  // 深海
  int BIOME_SEA = 1;      // 浅瀬
  int BIOME_SEASHORE = 2; // 海岸の砂浜
  int BIOME_MEADOW = 3;   // 草原 ( voronoi type = 0 )
  // int BIOME_FOREST = 4;    // 森 ( voronoi type = 1 )
  // int BIOME_DESERT = 5;    // 砂漠 ( voronoi type = 2 )
  // int BIOME_WASTELAND = 6; // 荒地 ( voronoi type = 3 )
  // int BIOME_POISONED = 7;  // 化学汚染 ( voronoi type = 4 )
  int BIOME_MOUNTAIN = 8; // 山岳
  int BIOME_SNOW = 9;     // 雪

  strategyMapBiomNo.init(resSize.x, resSize.y, 0);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float b = biom.pos2((8 * u) / (float)width, (8 * v) / (float)height);
      float height = strategyMapHF.getWithIgnoreOutOfRangeData(u, v);
      if (height < stratumLv[STRATUM_DEEPSEA])
      {
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, BIOME_DEEPSEA);
      }
      else if (height < stratumLv[STRATUM_SEA])
      {
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, BIOME_SEA);
      }
      else if (height < stratumLv[STRATUM_SEASHORE])
      {
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, BIOME_SEASHORE);
      }
      else if (height < stratumLv[STRATUM_PLAIN])
      {
        // 平地で様々な Biome が発生する
        int biomeType = b + BIOME_MEADOW;
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, biomeType);
      }
      else if (height < stratumLv[STRATUM_MOUNTAIN])
      {
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, BIOME_MOUNTAIN);
      }
      else if (height < stratumLv[STRATUM_SNOWMOUNTAIN])
      {
        strategyMapBiomNo.setWithIgnoreOutOfRangeData(u, v, BIOME_SNOW);
      }
    }
  }
}

float TerrainBaseLayerGenerator::getLayerHfAsWorldmapchip_StrategyLevel(const float u, const float v)
{
  int mapScale = conf.WorldScale;
  int layer1noisePointX = 1 * mapScale, layer1noisePointY = 1 * mapScale;
  int layer2noisePointX = 2 * mapScale, layer2noisePointY = 2 * mapScale;
  int layer3noisePointX = 3 * mapScale, layer3noisePointY = 3 * mapScale;
  int layer4noisePointX = 6 * mapScale, layer4noisePointY = 6 * mapScale;

  float wholeMapchipSizeWidth = conf.getWorldMapchipSize().x;
  float wholeMapchipSizeHeight = conf.getWorldMapchipSize().y;

  // 基本地形生成
  float res1 = layer1.pnoise2(
      (u * layer1noisePointX) / wholeMapchipSizeWidth,
      (v * layer1noisePointY) / wholeMapchipSizeHeight,
      layer1noisePointX, layer1noisePointY, 255.0f);

  float res2 = layer2.pnoise2(
      (u * layer2noisePointX) / wholeMapchipSizeWidth,
      (v * layer2noisePointY) / wholeMapchipSizeHeight,
      layer2noisePointX, layer2noisePointY, 255.0f);

  float res3 = layer3.pnoise2(
      (u * layer3noisePointX) / wholeMapchipSizeWidth,
      (v * layer3noisePointY) / wholeMapchipSizeHeight,
      layer3noisePointX, layer3noisePointY, 255.0f);

  float res4 = layer4.pnoise2(
      (u * layer4noisePointX) / wholeMapchipSizeWidth,
      (v * layer4noisePointY) / wholeMapchipSizeHeight,
      layer4noisePointX, layer4noisePointY, 255.0f);
  float hBase = res1 * 0.5f + res2 * 0.3f + res3 * 0.15f + res4 * 0.05f;

  // 外洋を作成
  float edgeFilterFix = edgeFileter.pos2(
      u / wholeMapchipSizeWidth,
      v / wholeMapchipSizeHeight);
  float hBaseFilter = hBase * edgeFilterFix;

  return hBaseFilter;
}

void TerrainBaseLayerGenerator::setConfig(TerrainBaseConfig _conf)
{
  conf = _conf;

  int biomeDivisionCount = _conf.BiomeDivisionSmallestCount * _conf.WorldScale;
  biom.init(_conf.Seed, _conf.NaturalBiomeTypes, biomeDivisionCount, biomeDivisionCount);
  layer1.init(_conf.Seed);
  layer2.init(_conf.Seed + 66);
  layer3.init(_conf.Seed + 100);
  layer4.init(_conf.Seed + 103);
  edgeFileter.init(_conf.mapEdgeWide / _conf.WorldScale);
}
