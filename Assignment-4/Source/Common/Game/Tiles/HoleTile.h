




#include "Tile.h"


class HoleTile : public Tile
{
public:
	HoleTile(const char* textureName = RES_TILE_HOLE);
	virtual ~HoleTile();
  
    //Return the type of the tile
    const char* getType();
};