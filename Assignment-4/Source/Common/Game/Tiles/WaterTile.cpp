




#include "WaterTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


WaterTile::WaterTile(const char* textureName) : Tile(TileTypeWater, textureName, false)
{

}

WaterTile::~WaterTile()
{

}

const char* WaterTile::getType()
{
    return TILE_WATER_TYPE;
}
