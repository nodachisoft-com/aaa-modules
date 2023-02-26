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
  strategyMapHF.init(resSize.x, resSize.y, 0.0f);

  {
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
  biom.init(_conf.Seed, (unsigned char)_conf.NaturalBiomeTypes, 32, 32);
  layer1.init(_conf.Seed);
  layer2.init(_conf.Seed + 66);
  layer3.init(_conf.Seed + 100);
  layer4.init(_conf.Seed + 103);
  edgeFileter.init(_conf.mapEdgeWide / _conf.WorldScale);
}

Memory2d<float> *TerrainBaseLayerGenerator::getStrategyMapHF()
{
  return &strategyMapHF;
}
