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
	m_BasicTower = new OpenGLTexture("TileTower");
    m_Ammo = 1000;
}

BasicTower::~BasicTower()
{

}

void BasicTower::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_BasicTower, getX(), getY(), getWidth(), getHeight());
    
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}

#pragma region Tower Upgrade Level
 
#pragma endregion
}

const char* BasicTower::getType()
{
	return BASIC_TOWER_TYPE;
}

int BasicTower::getHealth()
{
	return m_Health;
}