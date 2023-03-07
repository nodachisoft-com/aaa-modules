#pragma once
#include <iostream>
#include <ndclibs.hpp>
#include "TerrainConfig.hpp"
#include "TerrainBaseLayerGenerator.hpp"

namespace a3c
{
  class TerrainEngine
  {
    /// @brief BaseLayer 生成用エンジン
    TerrainBaseLayerGenerator baseLayerGen;

    /// @brief インスタンス初期化済みフラグ
    bool _initialized;

  public:
    /// @brief デフォルトコンストラクタ
    TerrainEngine();

    /// @brief
    ///   インスタンスに設定ファイルを渡し、メンバの各種 Generator に
    ///   必要な Config を渡す
    /// @param terrainConfig 地形生成用の Config
    void init(const TerrainConfig terrainConfig);

    /// @brief 新しく BaseLayer を生成する
    void generateNewBaseLayer();

  public: // ==== アクセサメソッド ====
    TerrainBaseLayerGenerator *getBaseLayerGenerator()
    {
      return &baseLayerGen;
    }
  };
}
