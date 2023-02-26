#pragma once
#include <iostream>
#include <vector>
#include <ndclibs.hpp>
#include "../TerrainBaseConfig.hpp"
#include "TerrainHfLayer.hpp"

using namespace nl;

namespace a3c
{
  /// @brief 地形の HF を生成する
  class TerrainHfGenerator
  {
  private:
    /// @brief 地形生成に必要な各種パラメータを取得する元
    TerrainBaseConfig conf;

    /// @brief 世界全体でのチップレベルでの数
    Size2d worldMapchipSize;

    /// @brief ストラテジー解析用（広域マップ）の解像度
    Size2d strategyMapUnitResolution;

  private:
    TerrainHfLayer hf1;
    TerrainHfLayer hf2;
    TerrainHfLayer hf3;
    TerrainHfLayer hf4;

  public:
    TerrainHfGenerator();
    TerrainHfGenerator(TerrainBaseConfig conf);

    bool init(TerrainBaseConfig conf);

    float getHeightAtWholemapChip(float u, float v);

    float getHeightAtStrategyResolution(float u, float v);

  public: // アクセサメソッド
    /// @brief 世界全体でのチップレベルでの数を取得
    Size2d getWorldMapchipSize()
    {
      return worldMapchipSize;
    }

    /// @brief ストラテジー解析用（広域マップ）の数を取得
    Size2d getStrategyMapUnitResolution()
    {
      return strategyMapUnitResolution;
    }
  };
}
