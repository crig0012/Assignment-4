//
//  ChestTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "ChestTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


ChestTile::ChestTile(const char* textureName) : Tile(TileTypeChest, textureName, true)
{
	
}

ChestTile::~ChestTile()
{

}

const char* ChestTile::getType()
{
    return TILE_CHEST_TYPE;
}
