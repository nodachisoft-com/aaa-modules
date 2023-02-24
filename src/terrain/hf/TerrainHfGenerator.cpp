#include "TerrainHfGenerator.hpp"

using namespace nl;
using namespace a3c;

TerrainHfGenerator::TerrainHfGenerator()
{
}
TerrainHfGenerator::TerrainHfGenerator(
    int randomSeed,
    MAPSIZE mapsize)
{
}

bool TerrainHfGenerator::init(
    int randomSeed,
    MAPSIZE mapsizeSelect)
{
  Vector2d mapsize;
  mapsize.x = 32 * 1024;
  mapsize.y = 32 * 1024;

  Vector2d noisePoint(6, 6);

  int mapScale = 1;
  if (mapsizeSelect == MAPSIZE::SMALL)
  {
    mapScale = 1;
  }
  else if (mapsizeSelect == MAPSIZE::MEDIUM)
  {
    mapScale = 2;
  }
  else
  { // LARGE
    mapScale = 4;
  }
  mapsize = mapsize * mapScale;
  noisePoint = noisePoint * mapScale;

  Rectangle2d windowArea({0, 0}, mapsize); // レンダリング範囲をマップサイズに合わせる
  hf1.init(0, randomSeed, windowArea, mapsize, noisePoint);
  hf2.init(0, randomSeed + 50, windowArea, mapsize, noisePoint * 2);
  hf3.init(0, randomSeed + 77, windowArea, mapsize, noisePoint * 3);
  hf4.init(0, randomSeed + 99, windowArea, mapsize, noisePoint * 6);
  return true;
}

// TODO: getHeight(WorldPosX, WorldPosY) で整数で位置を取得できるようにする
float TerrainHfGenerator::getHeight(int u, int v)
{
  Vector2d hf1WinArea = hf1.getWindowArea();

  float h = hf1.getHeight(u / hf1WinArea.x, v / hf1WinArea.y);
  return h;
}
