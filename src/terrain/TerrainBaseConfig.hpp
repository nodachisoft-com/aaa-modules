#pragma once
#include <iostream>
#include <ndclibs.hpp>

using namespace nl;

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

    /// @brief
    ///   World 生成時の SMALLEST サイズでの MapUnit のサイズを規定。
    ///   関連する値は以下で計算する
    ///   ・ World 全体でのマップチップサイズは、この値に scale（整数）と MapUnitSize をかけ合わせた数
    ///   ・ World 全体のストラテジー解析用サイズは、この値に scale（整数）をかけ合わせた数
    Size2d WorldSmallestMapunitSize;

    /// @brief SMALLEST サイズに対しての、生成する World のスケールサイズを指定。(x, y) はそれぞれ整数を指定する
    int WorldScale;

    /// @brief
    ///  1 つのマップユニットが持つ x 成分と y 成分の マップチップ数
    ///  例）32 なら、1つのマップユニットは 32 * 32 のマップチップを持つ
    int MapUnitChipSize;

  public:
    /// @brief Config をデフォルト値で初期化する
    TerrainBaseConfig();

    /// @brief World 全体でのマップチップサイズを取得する
    /// @return World 全体でのマップチップサイズ
    Size2d getWorldMapchipSize()
    {
      return WorldSmallestMapunitSize * WorldScale * MapUnitChipSize;
    }

    /// @brief World でのストラテジー解析用マップサイズを取得する
    /// @return World でのストラテジー解析用マップサイズ
    Size2d getStrategyResolutionSize()
    {
      return WorldSmallestMapunitSize * WorldScale;
    }
  };
}
