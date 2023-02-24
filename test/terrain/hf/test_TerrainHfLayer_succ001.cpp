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

// 縦ｘ横で 800x600 サイズのループ地形(HF)を TerrainHfLayer から生成する
// Layer の一部をカメラで拡大して、指定の部分を 800x600 解像度でレンダリングする
TEST(TerrainHfLayer, getHeight_case001)
{
  std::string pathPrefix = TESTTMP_DIR + "TerrainHfLayer_getHeight_case001_";

  float mapSizeX = 800 * 6;
  float mapSizeY = 600 * 6;
  float imgWidth = 400 * 1;
  float imgHeight = 300 * 1;
  Memory2d<float> strategyMapHF(imgWidth, imgHeight, 0.0f);

  Rectangle2d area1({0, 0}, {mapSizeX, mapSizeY}); // レンダリング範囲を指定
  TerrainHfLayer layer;

  layer.init(TerrainHfLayer::MODE_PPN, 101, area1, {mapSizeX, mapSizeY}, {8 * 6, 6 * 6});

  // 想定される結果
  unsigned long crc32expectList[] = {1431682718,
                                     999677722,
                                     2433758862};

  for (int i = 0; i < 3; i++)
  {
    float diff = (0.5f - 0.010f) / (3.0f - 1.0f);
    Rectangle2d viewWindow(
        {mapSizeX * diff * i, mapSizeY * diff * i},
        {mapSizeX * (1.0f - diff * i), mapSizeY * (1.0f - diff * i)});
    layer.setWindowArea(viewWindow);

    for (int v = 0; v < imgHeight; v++)
    {
      for (int u = 0; u < imgWidth; u++)
      {
        float h = layer.getHeight(u / imgWidth, v / imgHeight);
        strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
      }
    }
    std::string path = pathPrefix + std::to_string(i) + ".bmp";
    unsigned long crc32result = TestUtil::drawHfColorful(&strategyMapHF, path);
    EXPECT_EQ(crc32expectList[i], crc32result);
  }
}
