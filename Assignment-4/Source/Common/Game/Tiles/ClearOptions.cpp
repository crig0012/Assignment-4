//
//  GroundTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "ClearOptions.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


ClearOptions::ClearOptions(const char* textureName) : Tile(TileTypeGround, textureName, true)
{

}

ClearOptions::~ClearOptions()
{

}

const char* ClearOptions::getType()
{
    return 0;
}
