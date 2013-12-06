




#include "HoleTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


HoleTile::HoleTile(const char* textureName) : Tile(TileTypeHole, textureName, false)
{

}

HoleTile::~HoleTile()
{

}

const char* HoleTile::getType()
{
    return TILE_HOLE_TYPE;
}
