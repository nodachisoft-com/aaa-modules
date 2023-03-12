#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include <string>
#include "TerrainBaseConfig.hpp"
#include "Biome.hpp"
#include "../DBTables/DBs.hpp"

using namespace nl;

namespace a3c
{
  class TerrainGeoLabelGenerator
  {
  private:
    /// @brief 乱数生成器
    MtRandomizer rnd;

    /// @brief データベースへの参照
    DBs *dbRef;

  public:
    TerrainGeoLabelGenerator() : rnd(100), dbRef(nullptr)
    {
    }
    bool init(const int randomSeed, DBs &dbRef);

    std::string generateLabel(const Biome &biome);
  };
}
