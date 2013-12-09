//
//  WaterTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "SpawnPointEnemy.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


SpawnPointEnemy::SpawnPointEnemy(const char* textureName) : Tile(TileTypeSpawnEnemy, textureName, true)
{
    
}

SpawnPointEnemy::~SpawnPointEnemy()
{
    
}

const char* SpawnPointEnemy::getType()
{
    return TILE_SPAWN_ENEMY_TYPE;
}
