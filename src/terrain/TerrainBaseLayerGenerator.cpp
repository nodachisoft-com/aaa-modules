#include "TerrainBaseLayerGenerator.hpp"

using namespace a3c;

TerrainBaseLayerGenerator::TerrainBaseLayerGenerator()
{
  std::cout << "WAAA!" << std::endl;
}

void TerrainBaseLayerGenerator::setConfig(TerrainBaseConfig _conf)
{
  conf = _conf;
  biom = nl::NdcVoronoi(_conf.Seed, 3, 1024 * 4, 1024 * 4);
}

void TerrainBaseLayerGenerator::generateBaseTerrain()
{
}
