//
//  BasicTower.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-06.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//


#include "BasicTower.h"
#include "../../OpenGL/OpenGL.h"
#include "../Tiles/Tile.h"



BasicTower::BasicTower(Level* aLevel, int health) : Tower(aLevel, TowerTypeBasic),
	m_Health(health)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	m_TowerTexture = new OpenGLTexture("TileTower");
    m_Ammo = 1000;
}

BasicTower::~BasicTower()
{

}

const char* BasicTower::getType()
{
	return BASIC_TOWER_TYPE;
}

int BasicTower::getHealth()
{
	return m_Health;
}