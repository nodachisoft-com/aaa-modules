#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../src/a3commonlib.hpp"
#include "../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(TerrainBaseConfig, initialize_case001)
{
  TerrainBaseConfig conf;

  // 計算結果確認
  // EXPECT_EQ(0xed82cd11, result);
  // EXPECT_EQ(0xed82cd11, crc.getHash());
}
