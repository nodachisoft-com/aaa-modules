#pragma once
#include <iostream>
#include <vector>
#include <ndclibs.hpp>

using namespace nl;

namespace a3c
{
  /// @brief ノイズなどの個々のレイヤーを定義
  class TerrainHfLayer
  {
  public:
    static constexpr int MODE_PPN = 0;

  private:
    /// @brief 初期化済みなら true となる
    bool isInit;

    /// @brief 描画モード（0: ppn, 1: filter1, 2: filter2...）
    int mode;

    /// @brief ランダムシード
    int randomSeed;

    /// @brief 描画対象の範囲指定
    Rectangle2d windowArea;

    /// @brief マップサイズ
    Vector2d mapSize;

    /// @brief ノイズの密度を指定
    Vector2d noisePointSize;

    // mode0 で使用するフィルタ
    PerlinNoise1234 filter_mode0;

  public:
    /// @brief デフォルト値を設定する。別途 init 関数で初期化することを想定する
    TerrainHfLayer();

    /// @brief HeightField を生成するレイヤを初期化する
    /// @param mode ノイズパターンやフィルタパターンを指定
    /// @param randomSeed 乱数シードを指定
    /// @param windowArea 描画する対象の領域を指定
    /// @param mapSize 全体の幅、高さを指定
    /// @param noisePointSize Noise の密度を指定
    TerrainHfLayer(
        int mode,
        int randomSeed,
        Rectangle2d windowArea,
        Vector2d mapSize,
        Vector2d noisePointSize);

    /// @brief HeightField を生成するレイヤを初期化する
    /// @param mode ノイズパターンやフィルタパターンを指定
    /// @param randomSeed 乱数シードを指定
    /// @param windowArea 描画する対象の領域を指定
    /// @param mapSize 全体の幅、高さを指定
    /// @param noisePointSize Noise の密度を指定
    /// @return 初期化が成功したら true 。既に初期化済みなら false
    bool init(int mode,
              int randomSeed,
              Rectangle2d windowArea,
              Vector2d mapSize,
              Vector2d noisePointSize);

    /// @brief 描画する領域を設定する
    /// @param windowArea 描画する対象の領域を指定
    void setWindowArea(Rectangle2d windowArea);

    ~TerrainHfLayer();

    /// @brief
    /// @param u x 成分方向を指定。[0.0f - 1.0f] の範囲で指定すると、windowArea に収まる
    /// @param v y 成分方向を指定。[0.0f - 1.0f] の範囲で指定すると、windowArea に収まる
    float getHeight(float u, float v);

    Vector2d getWindowArea();
  };
};
