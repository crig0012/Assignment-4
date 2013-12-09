//
//  WaterTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__SpawnPointHero__
#define __GAM_1514_OSX_Game__SpawnPointHero__

#include "Tile.h"


class SpawnPointHero : public Tile
{
public:
	SpawnPointHero(const char* textureName = RES_TILE_WATER);
	virtual ~SpawnPointHero();
    
    //Return the type of the tile
    const char* getType();
};

#endif
