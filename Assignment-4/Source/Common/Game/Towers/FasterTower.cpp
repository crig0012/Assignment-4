//
//  FasterTower.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-11.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "FasterTower.h"
#include "../../OpenGL/OpenGL.h"
#include "../Tiles/Tile.h"

FasterTower::FasterTower(Level* aLevel, int health) : Tower(aLevel, TowerTypeBasic)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	m_TowerTexture = new OpenGLTexture("TowerFaster");
    m_Ammo = 1000;
    m_Health = health;
}

FasterTower::~FasterTower()
{
    
}

const char* FasterTower::getType()
{
	return BASIC_TOWER_TYPE;
}

int FasterTower::getHealth()
{
	return m_Health;
}