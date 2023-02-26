#include "TerrainHfLayer.hpp"

using namespace a3c;

TerrainHfLayer::TerrainHfLayer()
{
  isInit = false;
  Rectangle2d initRect({0.0f, 0.0f}, {1.0f, 1.0f});
  Vector2d begin(1.0f, 1.0f);
  Vector2d end(4.0f, 4.0f);
  init(0, 0, initRect, begin, end);
}

TerrainHfLayer::TerrainHfLayer(
    int mode,
    int randomSeed,
    Rectangle2d windowArea,
    Vector2d mapSize,
    Vector2d noisePointSize)
{
  init(mode, randomSeed, windowArea, mapSize, noisePointSize);
  isInit = true;
}

bool TerrainHfLayer::init(int _mode,
                          int _randomSeed,
                          Rectangle2d _windowArea,
                          Vector2d _mapSize,
                          Vector2d _noisePointSize)
{
  if (isInit)
  {
    return false;
  }
  mode = _mode;
  randomSeed = _randomSeed;
  windowArea = _windowArea;
  mapSize = _mapSize;
  noisePointSize = _noisePointSize;

  // フィルタのモードによって使用するノイズを切り替え
  switch (mode)
  {
  case 0: // PPN使用
    filter_mode0.init(randomSeed);
  case 1:
    break;
  default:
    break;
  }

  return true;
}

void TerrainHfLayer::setWindowArea(Rectangle2d _windowArea)
{
  windowArea = _windowArea;
}

TerrainHfLayer::~TerrainHfLayer()
{
}

float TerrainHfLayer::getHeight(float u, float v)
{
  Vector2d LeftUpper = windowArea.getLeftUpperPoint();
  float worldPosU = LeftUpper.x + u * windowArea.getWidth();
  float worldPosV = LeftUpper.y + v * windowArea.getHeight();
  float res1 = filter_mode0.pnoise2(
      (worldPosU * noisePointSize.x) / (float)mapSize.x,
      (worldPosV * noisePointSize.y) / (float)mapSize.y,
      noisePointSize.x, noisePointSize.y, 255.0f);
  return res1;
}

Rectangle2d TerrainHfLayer::getWindowArea()
{
  return windowArea;
}
