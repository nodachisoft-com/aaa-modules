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

    /// @brief Terrain layer1 ( Strategy Use )
    PerlinNoise1234 layer1;

    /// @brief Terrain layer2 ( Strategy Use )
    PerlinNoise1234 layer2;

    /// @brief Terrain layer3 ( Strategy Use )
    PerlinNoise1234 layer3;

    /// @brief Terrain layer4 ( Strategy Use )
    PerlinNoise1234 layer4;

    /// @brief マップ縁を海に鎮めるフィルタ
    EdgeNoiseCurveFilter edgeFileter;

    /// @brief Strategy 計算用の大域マップデータ（HF）を生成する
    Memory2d<float> strategyMapHF;

  public:
    TerrainBaseLayerGenerator();
    ~TerrainBaseLayerGenerator();

    // 基本的 Terrain, History, Ruin, Organization, Map DestructionArea 作成
    void generateBaseTerrain();

    float getWorldmapchipHf(const float u, const float v);

  private:
    float getLayerHfAsWorldmapchip_StrategyLevel(const float u, const float v);

  public:
    // ============= アクセサメソッド ===============
    /// @brief
    ///  マップ生成に必要な情報を config 形式で設定する。
    ///  マップ生成には generateBaseTerrain を別途呼び出しする必要がある
    /// @param conf マップ生成に必要な情報
    void setConfig(TerrainBaseConfig conf);

    /// @brief 大域用マップデータの HeightField への参照を取得する
    /// @return
    Memory2d<float> *getStrategyMapHF();
  };
}
