




#include "Tile.h"


class GrassTile : public Tile
{
public:
	GrassTile(const char* textureName = RES_TILE_GRASS);
	virtual ~GrassTile();
  
    //Return the type of the tile
    const char* getType();

	float getTileSpeed();

};