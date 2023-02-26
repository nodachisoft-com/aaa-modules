#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include "TerrainBaseConfig.hpp"

using namespace nl;

namespace a3c
{
  class Biome
  {
  private:
    /// @brief Strategy Map 上のユニークな Biome 番号
    int biomeNo;

    /// @brief Biome の種類
    int biomKind;

  public:
    Biome() : biomeNo(0), biomKind(0){};
  };
}
