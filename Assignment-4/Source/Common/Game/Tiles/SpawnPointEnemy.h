//
//  WaterTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__SpawnPointEnemy__
#define __GAM_1514_OSX_Game__SpawnPointEnemy__

#include "Tile.h"


class SpawnPointEnemy : public Tile
{
public:
	SpawnPointEnemy(const char* textureName = RES_TILE_TOWER);
	virtual ~SpawnPointEnemy();
    
    //Return the type of the tile
    const char* getType();
};

#endif


