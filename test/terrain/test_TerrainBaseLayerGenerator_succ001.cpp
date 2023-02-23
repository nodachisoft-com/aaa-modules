#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../src/a3commonlib.hpp"
#include "../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(TerrainBaseLayerGenerator, initialize_case001)
{

  TerrainBaseConfig conf;

  conf.Seed = 100;
  conf.NaturalBiomeTypes = 4;
  conf.WorldMapWidth = 1024 * 64;
  conf.WorldMapHeight = 1024 * 64;

  TerrainBaseLayerGenerator terrainGenerator;
  terrainGenerator.setConfig(conf);

  // Logger log;
  // log.infoLog("terrainGenerator.setConfig finish");

  //
  terrainGenerator.generateBaseTerrain();

  // log.infoLog("terrainGenerator.generateBaseTerrain finish");

  // デバッグ画像出力
  // DEBUG 用の画像出力

  Memory2d<float> *hf = terrainGenerator.getStrategyMapHF();
  /*
  int width = hf->getWidth();
  int height = hf->getHeight();
  BitmapImage image(width, height);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float res = hf->getWithIgnoreOutOfRangeData(u, v);
      unsigned char color_elem = (unsigned char)res;
      ColorRGB color{color_elem, color_elem, color_elem};
      image.set(u, v, color);
    }
  }
  image.WriteBmp("./debug/0000_test.bmp");
  */
  TestUtil::drawHfColorful(hf, "./debug/0000_test.bmp");

  // 計算結果確認
  // EXPECT_EQ(0xed82cd11, result);
  // EXPECT_EQ(0xed82cd11, crc.getHash());
}
