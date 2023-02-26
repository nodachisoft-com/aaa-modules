#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../src/a3commonlib.hpp"
#include "../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(TerrainBaseLayerGenerator, getStrategyMapHF_case001)
{

  TerrainBaseConfig conf;
  conf.Seed = 101;
  conf.NaturalBiomeTypes = 4;
  conf.WorldSmallestMapunitSize = Size2d(256, 256);
  conf.WorldScale = 4;
  conf.mapEdgeWide = 0.4f;

  TerrainBaseLayerGenerator terrainGenerator;
  terrainGenerator.setConfig(conf);
  terrainGenerator.generateBaseTerrain();

  // デバッグ画像出力
  Memory2d<float> *hf = terrainGenerator.getStrategyMapHF();
  TestUtil::drawHfColorful(hf, TESTTMP_DIR + "getStrategyMapHF_001.bmp");

  // 計算結果確認
  // EXPECT_EQ(0xed82cd11, result);
  // EXPECT_EQ(0xed82cd11, crc.getHash());
}
