//
//  TowerTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "TowerTile.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


TowerTile::TowerTile(const char* textureName) : Tile(TileTypeTower, textureName, true)
{
    m_IsWalkableTile = false;
}

TowerTile::~TowerTile()
{

}

const char* TowerTile::getType()
{
    return TILE_TOWER_TYPE;
}
