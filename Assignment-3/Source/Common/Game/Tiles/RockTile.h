




#include "Tile.h"


class RockTile : public Tile
{
public:
	RockTile(const char* textureName = RES_TILE_ROCK);
	virtual ~RockTile();
  
    //Return the type of the tile
    const char* getType();
};