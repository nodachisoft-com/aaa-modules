#include "TerrainBaseConfig.hpp"

using namespace a3c;

TerrainBaseConfig::TerrainBaseConfig()
    : Seed(0),
      NaturalBiomeTypes(4),
      WorldSmallestMapunitSize({64, 64}),
      WorldScale(1),
      MapUnitChipSize(32),
      mapEdgeWide(0.2f)
{
}
