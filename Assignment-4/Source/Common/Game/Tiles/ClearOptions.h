//
//  GroundTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef CLEAR_OPTIONS_H
#define CLEAR_OPTIONS_H

#include "Tile.h"


class ClearOptions : public Tile
{
public:
	ClearOptions(const char* textureName);
	virtual ~ClearOptions();
  
    //Return the type of the tile
    const char* getType();
};

#endif
