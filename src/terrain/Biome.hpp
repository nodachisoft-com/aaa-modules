#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include "TerrainBaseConfig.hpp"

using namespace nl;

namespace a3c
{
  class Biome
  {
  public:
    /// @brief Strategy Map 上のユニークな Biome 番号
    int biomeNo;

    /// @brief Biome の種類
    int biomeKind;

    /// @brief Biome の面積
    int biomeAreaSize;

    /// @brief Biome の中心点
    Point2d centerPos;

    /// @brief Label名
    std::string labelName;

  public:
    Biome() : biomeNo(0), biomeKind(0), biomeAreaSize(0), centerPos(0.0f, 0.0f),
              labelName(""){};
  };
}
