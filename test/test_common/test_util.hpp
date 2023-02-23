#pragma once
#include <vector>
#include <ndclibs.hpp>

using namespace nl;

namespace TestUtil
{
  static ColorRGB getColorByHeight(float res)
  {
    struct Stratum
    {
      float hFrom, hTo;
      ColorRGB cFrom, cTo;
    };

    std::vector<Stratum> stratumList;

    // 条件漏れを目視できるように赤色
    ColorRGB result{255, 0, 0};

    // 海（深海）
    float SEA1_LV_DEPTH = 0.0f, SEA1_LV_UP = 100.0f;           // 高さ（深い～浅い）
    ColorRGB SEA1_C_DEPTH{0, 87, 232}, SEA1_C_UP{43, 73, 249}; // 色（深い～浅い）

    // 海（浅瀬）
    float SEA2_LV_DEPTH = 100.0f, SEA2_LV_UP = 120.0f;            // 高さ（深い～浅い）
    ColorRGB SEA2_C_DEPTH{43, 73, 249}, SEA2_C_UP{162, 199, 221}; // 色（深い～浅い）

    // 砂浜
    float SHORE_LV_DEPTH = 120.0f, SHORE_LV_UP = 123.0f;              // 高さ（深い～浅い）
    ColorRGB SHORE_C_DEPTH{255, 252, 147}, SHORE_C_UP{255, 239, 130}; // 色（深い～浅い）

    // 海(深海)の高さ判定・色設定
    if (SEA1_LV_DEPTH <= res && res < SEA1_LV_UP)
    {
      float alpha = (res - SEA1_LV_DEPTH) / (SEA1_LV_UP - SEA1_LV_DEPTH);
      result.r = SEA1_C_UP.r * alpha + SEA1_C_DEPTH.r * (1.0f - alpha);
      result.g = SEA1_C_UP.g * alpha + SEA1_C_DEPTH.g * (1.0f - alpha);
      result.b = SEA1_C_UP.b * alpha + SEA1_C_DEPTH.b * (1.0f - alpha);
    }
    // 海(浅瀬)の高さ判定・色設定
    else if (SEA2_LV_DEPTH <= res && res < SEA2_LV_UP)
    {
      float alpha = (res - SEA2_LV_DEPTH) / (SEA2_LV_UP - SEA2_LV_DEPTH);
      result.r = SEA2_C_UP.r * alpha + SEA2_C_DEPTH.r * (1.0f - alpha);
      result.g = SEA2_C_UP.g * alpha + SEA2_C_DEPTH.g * (1.0f - alpha);
      result.b = SEA2_C_UP.b * alpha + SEA2_C_DEPTH.b * (1.0f - alpha);
    }
    // 砂浜の高さ判定・色設定
    else if (SHORE_LV_DEPTH <= res && res < SHORE_LV_UP)
    {
      float alpha = (res - SHORE_LV_DEPTH) / (SHORE_LV_UP - SHORE_LV_DEPTH);
      result.r = SHORE_C_UP.r * alpha + SHORE_C_DEPTH.r * (1.0f - alpha);
      result.g = SHORE_C_UP.g * alpha + SHORE_C_DEPTH.g * (1.0f - alpha);
      result.b = SHORE_C_UP.b * alpha + SHORE_C_DEPTH.b * (1.0f - alpha);
    }
    else
    {
      result.r = (unsigned char)res;
      result.g = (unsigned char)res;
      result.b = (unsigned char)res;
    }
    return result;
  }

  /// @brief 生成された HeightField を視覚的に確認するためのテスト用画像出力関数
  /// @param hf HeightField を格納した2次元データ。高さ情報として 0.0F-255.0F が格納される
  /// @param filepath
  static void drawHfColorful(Memory2d<float> *hf, const std::string filepath)
  {
    int width = hf->getWidth();
    int height = hf->getHeight();
    BitmapImage image(width, height);
    for (int v = 0; v < height; v++)
    {
      for (int u = 0; u < width; u++)
      {
        float res = hf->getWithIgnoreOutOfRangeData(u, v);
        ColorRGB color = getColorByHeight(res);
        image.set(u, v, color);
      }
    }
    image.WriteBmp(filepath);
  }
}
