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
  layer3.init(_conf.Seed + 100);
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
    int layer1noisePointX = 4, layer1noisePointY = 4;
    int layer2noisePointX = 8, layer2noisePointY = 8;
    int layer3noisePointX = 12, layer3noisePointY = 12;
    for (int v = 0; v < height; v++)
    {
      for (int u = 0; u < width; u++)
      {
        float res1 = layer1.pnoise2(
            (u * layer1noisePointX) / (float)width,
            (v * layer1noisePointY) / (float)height,
            layer1noisePointX, layer1noisePointY, 255.0f);

        float res2 = layer2.pnoise2(
            (u * layer2noisePointX) / (float)width,
            (v * layer2noisePointY) / (float)height,
            layer2noisePointX, layer2noisePointY, 255.0f);

        float res3 = layer3.pnoise2(
            (u * layer3noisePointX) / (float)width,
            (v * layer3noisePointY) / (float)height,
            layer3noisePointX, layer3noisePointY, 255.0f);
        float res = res1 * 0.5 + res2 * 0.3 + res3 * 0.2;
        // float res = res1 * 0.7 + res2 * 0.3;
        // float res = res1;

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
  image.WriteBmp("./debug/0000_test.bmp");
  std::cout << "Bitmap Released!" << std::endl;
}
