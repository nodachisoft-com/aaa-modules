#include <gtest/gtest.h>
#include <ndclibs.hpp>
#include <iostream>
#include "../../src/a3commonlib.hpp"
#include "../test_common/index.hpp"

using namespace nl;
using namespace a3c;

TEST(DBs, initialize_case001)
{
  DBs DBs;
  DBs.init();

  std::cout << DBs.TABLE_LABELS_GEO.size() << std::endl;

  EXPECT_GT(DBs.TABLE_LABELS_GEO.size(), 1);

  // 計算結果確認
  // EXPECT_EQ(0xed82cd11, result);
  // EXPECT_EQ(0xed82cd11, crc.getHash());
}
