




#include "TreeTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


TreeTile::TreeTile(const char* textureName) : Tile(TileTypeTree, textureName, false)
{

}

TreeTile::~TreeTile()
{

}

const char* TreeTile::getType()
{
    return TILE_TREE_TYPE;
}
