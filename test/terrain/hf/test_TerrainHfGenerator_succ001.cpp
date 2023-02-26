#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../../src/a3commonlib.hpp"
#include "../../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(TerrainHfGenerator, initialize_case001)
{
  TerrainBaseConfig conf;
  conf.NaturalBiomeTypes = 5;
  conf.Seed = 100;
  conf.WorldSmallestMapunitSize = Size2d(1024, 1024);
  conf.WorldScale = 5;
  conf.MapUnitChipSize = 64;

  TerrainHfGenerator gen;
  EXPECT_EQ(gen.init(conf), true);
}

// 縦ｘ横で 800x600 サイズのループ地形(HF)を TerrainHfLayer から生成する
// Layer の一部をカメラで拡大して、指定の部分を 800x600 解像度でレンダリングする
TEST(TerrainHfGenerator, getHeight_case001)
{
  std::string pathPrefix = TESTTMP_DIR + "TerrainHfGenerator_getHeight_case001_";

  TerrainBaseConfig conf;
  conf.NaturalBiomeTypes = 5;
  conf.Seed = 100;
  conf.WorldSmallestMapunitSize = Size2d(1024, 1024);
  conf.WorldScale = 2;
  conf.MapUnitChipSize = 32;

  TerrainHfGenerator gen;
  gen.init(conf);

  // 試しに画像生成してみる
  float imgWidth = 512;
  float imgHeight = 512;
  Memory2d<float> strategyMapHF(imgWidth, imgHeight, 0.0f);

  Size2d strategyMapResolution = gen.getStrategyMapUnitResolution();
  float diffU = strategyMapResolution.x / imgWidth;
  float diffV = strategyMapResolution.y / imgHeight;
  for (int v = 0; v < imgHeight; v++)
  {
    for (int u = 0; u < imgWidth; u++)
    {
      float h = gen.getHeightAtStrategyResolution(u * diffU, v * diffV);
      strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
    }
  }

  std::string path = pathPrefix + std::to_string(0) + ".bmp";
  // unsigned long crc32result = TestUtil::drawHfColorful(&strategyMapHF, path);
  TestUtil::drawHfColorful(&strategyMapHF, path);
  // EXPECT_EQ(crc32expectList[i], crc32result);
}
