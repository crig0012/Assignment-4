//
//  ChestTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef CHEST_TILE_H
#define CHEST_TILE_H

#include "Tile.h"


class ChestTile : public Tile
{
public:
	ChestTile(const char* textureName = RES_TILE_CHEST);
	virtual ~ChestTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif
