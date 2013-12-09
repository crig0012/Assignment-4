//
//  WaterTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "SpawnPointHero.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


SpawnPointHero::SpawnPointHero(const char* textureName) : Tile(TileTypeSpawnHero, textureName, true)
{
    
}

SpawnPointHero::~SpawnPointHero()
{
    
}

const char* SpawnPointHero::getType()
{
    return TILE_SPAWN_HERO_TYPE;
}
