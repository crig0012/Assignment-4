//
//  ChestTile.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef EXIT_OPTIONS_H
#define EXIT_OPTIONS_H

#include "Tile.h"


class ExitOptions : public Tile
{
public:
	ExitOptions(const char* textureName);
	virtual ~ExitOptions();
  
    //Return the type of the tile
    const char* getType();
};

#endif
