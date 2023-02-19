#pragma once
#include <iostream>
#include <ndclibs.hpp>

namespace a3c
{
  /// @brief World Map のベースとなる生成のための各種パラメータを定義
  class TerrainBaseConfig
  {
  public:
    /// @brief 生成の種で利用
    int Seed;

    /// @brief 自然発生する Biome の種類数を指定
    int NaturalBiomeTypes;

    /// @brief World Map の全体のチップサイズの幅を指定
    int WorldMapWidth;

    /// @brief World Map の全体のチップサイズの高さを指定
    int WorldMapHeight;

    /// @brief Config をデフォルト値で初期化する
    TerrainBaseConfig();
  };
}
