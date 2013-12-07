




#include "RockTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


RockTile::RockTile(const char* textureName) : Tile(TileTypeRock, textureName, false)
{

}

RockTile::~RockTile()
{

}

const char* RockTile::getType()
{
    return TILE_ROCK_TYPE;
}
