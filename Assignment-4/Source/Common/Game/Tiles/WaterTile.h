



#include "Tile.h"


class WaterTile : public Tile
{
public:
	WaterTile(const char* textureName = RES_TILE_WATER);
	virtual ~WaterTile();
  
    //Return the type of the tile
    const char* getType();
};