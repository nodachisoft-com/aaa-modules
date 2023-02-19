#pragma once
#include <iostream>
#include <vector>
#include <ndclibs.hpp>

namespace a3c
{
  /// @brief ノイズなどの個々のレイヤーを定義
  class TerrainLayer
  {
    int mode; /// @brief 描画モード（0: ppn, 1: filter1, 2: filter2...）
    int randomSeed;
    int dataFromX; /// @brief データとしての最大解像度
    int dataFromY; /// @brief データとしての最大解像度
    int dataToX;
    int dataToY;

    /// @brief データ取得する際の解像度
    int drawWidth;
    /// @brief データ取得する際の解像度
    int drawHeight;
    int noisePointX;
    int noisePointY;

    nl::PerlinNoise1234 *filter_mode0 = nullptr;

    TerrainLayer(
        int mode,
        int _randomSeed,
        int dataFromX, int dataFromY, int dataToX, int dataToY,
        int drawWidth, int drawHeight,
        int noisePointX, int noisePointY) : mode(mode), randomSeed(_randomSeed), dataFromX(dataFromX), dataFromY(dataFromY), dataToX(dataToX), dataToY(dataToY), drawWidth(drawWidth), drawHeight(drawHeight), noisePointX(noisePointX), noisePointY(noisePointY)
    {
      switch (mode)
      {
      case 0: // PPN使用
        filter_mode0 = new nl::PerlinNoise1234(_randomSeed);
      case 1:
        break;
      default:
        break;
      }
    }

    ~TerrainLayer()
    {
      switch (mode)
      {
      case 0: // PPN使用
        delete filter_mode0;
      case 1:
        break;
      default:
        break;
      }
    }

    float getHeight(int u, int v)
    {
      return 0.0f;
    }
  };

  /// @brief Perlin Noise などのレイヤー組み合わせて地形の Hight Field を生成する
  class TerrainHightmapGenerator
  {
  private:
    int width;
    int height;
    // std::vector<TerrainLayer> layers;

  public:
    TerrainHightmapGenerator();
    bool init();
  };
};
