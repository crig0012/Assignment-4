




#include "Tile.h"


class TreeTile : public Tile
{
public:
	TreeTile(const char* textureName = RES_TILE_TREE);
	virtual ~TreeTile();
  
    //Return the type of the tile
    const char* getType();
};