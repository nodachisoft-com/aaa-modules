#include "MapEngine.hpp"

using namespace a3c;

MapEngine::MapEngine()
{
  initialized = false;
};

void MapEngine::init(const MapConfig _mapConfig)
{
  mapConfig = _mapConfig;
}

void MapEngine::generateNewWorld()
{
  terrainEngine.init(mapConfig.terrainConfig);
}
