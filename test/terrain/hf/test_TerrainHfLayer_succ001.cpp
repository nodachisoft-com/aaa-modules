#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../../src/a3commonlib.hpp"
#include "../../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(TerrainHfLayer, initialize_case001)
{
  TerrainHfLayer layer;
  Rectangle2d area({0, 0}, {1024, 1024});
  bool result = layer.init(TerrainHfLayer::MODE_PPN, 100, area, {1024, 1024}, {8, 8});
  EXPECT_EQ(result, true);
}

// 縦ｘ横で 1024x1024 サイズのループ地形(HF)を TerrainHfLayer から生成する
TEST(TerrainHfLayer, getHeight_case001)
{
  std::string path1 = TESTTMP_DIR + "TerrainHfLayer_getHeight_case001_1.bmp";
  std::string path2 = TESTTMP_DIR + "TerrainHfLayer_getHeight_case001_2.bmp";
  std::string path3 = TESTTMP_DIR + "TerrainHfLayer_getHeight_case001_3.bmp";

  float width = 800;
  float height = 600;
  Memory2d<float> strategyMapHF(width, height, 0.0f);

  Rectangle2d area1({0, 0}, {width, height});
  TerrainHfLayer layer;
  layer.init(TerrainHfLayer::MODE_PPN, 101, area1, {width, height}, {8, 6});
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float h = layer.getHeight(u / width, v / height);
      strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
    }
  }
  TestUtil::drawHfColorful(&strategyMapHF, path1);

  // 同じマップの一部(80%部分)を拡大する(中央部分)
  Rectangle2d area2({width * 0.1f, height * 0.1f}, {width * 0.9f, height * 0.9f});
  layer.setWindowArea(area2);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float h = layer.getHeight(u / width, v / height);
      strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
    }
  }
  TestUtil::drawHfColorful(&strategyMapHF, path2);

  // 同じマップの一部(60%部分)を拡大する(中央部分)
  Rectangle2d area3({width * 0.2f, height * 0.2f}, {width * 0.8f, height * 0.8f});
  layer.setWindowArea(area3);
  for (int v = 0; v < height; v++)
  {
    for (int u = 0; u < width; u++)
    {
      float h = layer.getHeight(u / width, v / height);
      strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
    }
  }
  TestUtil::drawHfColorful(&strategyMapHF, path3);
}
