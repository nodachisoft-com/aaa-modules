#include "TerrainBaseLayerGenerator.hpp"

using namespace a3c;
using namespace nl;

TerrainBaseLayerGenerator::TerrainBaseLayerGenerator()
{
}

TerrainBaseLayerGenerator::~TerrainBaseLayerGenerator()
{
}

void TerrainBaseLayerGenerator::setConfig(TerrainBaseConfig _conf)
{
  conf = _conf;
  biom.init(_conf.Seed, (unsigned char)_conf.NaturalBiomeTypes, 32, 32);
  layer1.init(_conf.Seed);
  layer2.init(_conf.Seed + 66);
}

void TerrainBaseLayerGenerator::generateBaseTerrain()
{
  // Continents/Biom などの基本的な地理情報を 1024 x 1024 で生成し、
  // 勢力図、経路情報の生成に使用する
  int width = 1024;
  int height = 1024;
  strategyMapHF.init(width, height, 0.0f);
  // レイヤー1
  {
    int noisePointX = 4;
    int noisePointY = 4;
    for (int v = 0; v < height; v++)
    {
      for (int u = 0; u < width; u++)
      {
        float res = layer1.pnoise2((u * noisePointX) / (float)width, (v * noisePointY) / (float)height, noisePointX, noisePointY, 255.0f);
        strategyMapHF.setWithIgnoreOutOfRangeData(u, v, res);
      }
    }
  }

  // レイヤー2
  {
    int noisePointX = 8;
    int noisePointY = 8;
    for (int v = 0; v < height; v++)
    {
      for (int u = 0; u < width; u++)
      {
        float res = layer2.pnoise2((u * noisePointX) / (float)width, (v * noisePointY) / (float)height, noisePointX, noisePointY, 255.0f);
        strategyMapHF.setWithIgnoreOutOfRangeData(u, v, res);
      }
    }
  }

  // デバッグ画像出力
  // DEBUG 用の画像出力
  BitmapImage image(width, height);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float res = strategyMapHF.getWithIgnoreOutOfRangeData(u, v);
      unsigned char color_elem = (unsigned char)res;
      ColorRGB color{color_elem, color_elem, color_elem};
      image.set(u, v, color);
    }
  }
  image.WriteBmp("0000_test.bmp");
}
