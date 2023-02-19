#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include "TerrainBaseConfig.hpp"

namespace a3c
{
  class TerrainBaseLayerGenerator
  {
  private:
    TerrainBaseConfig conf;

    /// @brief Biome 生成。設定値は setConfig で上書きされる
    nl::NdcVoronoi biom{0, 4, 64, 64};

  public:
    TerrainBaseLayerGenerator();
    void setConfig(TerrainBaseConfig conf);

    // 基本的 Terrain, History, Ruin, Organization, Map DestructionArea 作成
    void generateBaseTerrain();
  };
}
