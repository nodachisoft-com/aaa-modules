#include "TerrainEngine.hpp"

using namespace a3c;

TerrainEngine::TerrainEngine()
{
  // 初期化未済のフラグをたてる
  _initialized = false;
}

void TerrainEngine::init(const TerrainConfig terrainConfig)
{
  // TerrainBaseLayerGenerator を初期化する
  baseLayerGen.init(terrainConfig.terrainBaseConfig);
  _initialized = true; // 初期化済みフラグをたてる
}

void TerrainEngine::generateNewBaseLayer()
{
  // BaseLayer の HF、Biome、NamedPlace のポイントを生成する
  baseLayerGen.generateBaseTerrain();
}
