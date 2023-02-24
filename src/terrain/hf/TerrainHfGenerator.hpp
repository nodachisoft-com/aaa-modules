#pragma once
#include <iostream>
#include <vector>
#include <ndclibs.hpp>
#include "TerrainHfLayer.hpp"

using namespace nl;

namespace a3c
{
  /// @brief 地形の HF を生成する
  class TerrainHfGenerator
  {
  public:
    enum MAPSIZE
    {
      SMALL,
      MEDIUM,
      LARGE
    };

  private:
    TerrainHfLayer hf1;
    TerrainHfLayer hf2;
    TerrainHfLayer hf3;
    TerrainHfLayer hf4;

  public:
    TerrainHfGenerator();
    TerrainHfGenerator(
        int randomSeed,
        MAPSIZE mapsize);

    bool init(
        int randomSeed,
        MAPSIZE mapsize);

    // TODO: 作成
    float getHeight(int u, int v);
  };
}
