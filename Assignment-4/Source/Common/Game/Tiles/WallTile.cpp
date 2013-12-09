//
//  WallTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "WallTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


WallTile::WallTile(const char* textureName) : Tile(TileTypeWall, textureName, true)
{

}

WallTile::~WallTile()
{

}

const char* WallTile::getType()
{
    return TILE_WALL_TYPE;
}
