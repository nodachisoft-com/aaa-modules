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

  float mapSizeX = 800;
  float mapSizeY = 600;
  float imgWidth = 400;
  float imgHeight = 300;
  Memory2d<float> strategyMapHF(imgWidth, imgHeight, 0.0f);

  Rectangle2d area1({0, 0}, {mapSizeX, mapSizeY}); // レンダリング範囲を指定
  TerrainHfLayer layer;
  // TODO : noize 濃度を 0.0-1.0 で指定可能とすること
  layer.init(TerrainHfLayer::MODE_PPN, 101, area1, {mapSizeX, mapSizeY}, {8, 6});

  for (int i = 0; i < 7; i++)
  {
    float diff = 0.0485f;
    Rectangle2d viewWindow(
        {imgWidth * diff * i, imgHeight * diff * i},
        {imgWidth * (1.0f - diff * i), imgHeight * (1.0f - diff * i)});
    layer.setWindowArea(viewWindow);

    for (int v = 0; v < imgHeight; v++)
    {
      for (int u = 0; u < imgWidth; u++)
      {
        float h = layer.getHeight(u / imgWidth, v / imgHeight);
        strategyMapHF.setWithIgnoreOutOfRangeData(u, v, h);
      }
    }
    TestUtil::drawHfColorful(&strategyMapHF, pathPrefix + std::to_string(i) + ".bmp");
  }
}
