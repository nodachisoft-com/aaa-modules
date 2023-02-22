#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include "TerrainBaseConfig.hpp"

using namespace nl;

namespace a3c
{
  class TerrainBaseLayerGenerator
  {
  private:
    TerrainBaseConfig conf;

    /// @brief Biome
    NdcVoronoi biom;

    /// @brief Terrain layer1
    PerlinNoise1234 layer1;

    /// @brief Terrain layer2
    PerlinNoise1234 layer2;

    /// @brief Terrain layer3
    PerlinNoise1234 layer3;

    /// @brief Strategy 計算用の大域マップデータ（HF）を生成する
    Memory2d<float> strategyMapHF;

  public:
    TerrainBaseLayerGenerator();
    ~TerrainBaseLayerGenerator();
    void setConfig(TerrainBaseConfig conf);

    // 基本的 Terrain, History, Ruin, Organization, Map DestructionArea 作成
    void generateBaseTerrain();
  };
}
