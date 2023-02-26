#include "TerrainHfGenerator.hpp"

using namespace nl;
using namespace a3c;

TerrainHfGenerator::TerrainHfGenerator()
{
}
TerrainHfGenerator::TerrainHfGenerator(
    TerrainBaseConfig conf)
    : conf(conf)
{
}

bool TerrainHfGenerator::init(
    TerrainBaseConfig _conf)
{
  conf = _conf;
  // 世界全体でのチップレベルでの数を設定
  worldMapchipSize = conf.getWorldMapchipSize();

  // ノイズの生成の数を定義
  Vector2d noisePoint = Vector2d(6, 6) * conf.WorldScale;

  // ストラテジー解析用（広域マップ）の解像度を設定
  strategyMapUnitResolution = conf.getStrategyResolutionSize();
  int randomSeed = conf.Seed;

  // 各種の地形生成モジュールを初期化する
  Rectangle2d windowArea({0, 0}, worldMapchipSize); // レンダリング範囲をマップサイズに合わせる
  hf1.init(0, randomSeed, windowArea, worldMapchipSize, noisePoint);
  hf2.init(0, randomSeed + 50, windowArea, worldMapchipSize, noisePoint * 2);
  hf3.init(0, randomSeed + 77, windowArea, worldMapchipSize, noisePoint * 3);
  hf4.init(0, randomSeed + 99, windowArea, worldMapchipSize, noisePoint * 6);
  return true;
}

// TODO: getHeight(WorldPosX, WorldPosY) で整数で位置を取得できるようにする
float TerrainHfGenerator::getHeightAtWholemapChip(float u, float v)
{
  float h = 0.0f;
  h += hf1.getHeight(u / worldMapchipSize.x, v / worldMapchipSize.y) * 0.5;
  h += hf2.getHeight(u / worldMapchipSize.x, v / worldMapchipSize.y) * 0.2;
  h += hf3.getHeight(u / worldMapchipSize.x, v / worldMapchipSize.y) * 0.2;
  h += hf4.getHeight(u / worldMapchipSize.x, v / worldMapchipSize.y) * 0.1;
  return h;
}

float TerrainHfGenerator::getHeightAtStrategyResolution(float u, float v)
{
  float h = 0.0f;
  float uSt = u * conf.MapUnitChipSize * conf.WorldScale;
  float vSt = v * conf.MapUnitChipSize * conf.WorldScale;
  h += hf1.getHeight(uSt / worldMapchipSize.x, vSt / worldMapchipSize.y) * 0.5;
  h += hf2.getHeight(uSt / worldMapchipSize.x, vSt / worldMapchipSize.y) * 0.2;
  h += hf3.getHeight(uSt / worldMapchipSize.x, vSt / worldMapchipSize.y) * 0.2;
  h += hf4.getHeight(uSt / worldMapchipSize.x, vSt / worldMapchipSize.y) * 0.1;
  return h;
}
