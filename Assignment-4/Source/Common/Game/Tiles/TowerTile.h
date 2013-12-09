//
//  TowerTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef TOWER_TILE_H
#define TOWER_TILE_H

#include "Tile.h"


class TowerTile : public Tile
{
public:
	TowerTile(const char* textureName = RES_TILE_TOWER);
	virtual ~TowerTile();
  
    //Return the type of the tile
    const char* getType();
};

#endif
