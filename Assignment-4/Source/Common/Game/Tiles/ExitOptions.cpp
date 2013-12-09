//
//  ChestTile.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "ExitOptions.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Constants/Constants.h"


ExitOptions::ExitOptions(const char* textureName) : Tile(TileTypeChest, textureName, true)
{
	
}

ExitOptions::~ExitOptions()
{

}

const char* ExitOptions::getType()
{
    return 0;
}
