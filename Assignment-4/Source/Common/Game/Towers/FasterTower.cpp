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

FasterTower::FasterTower(Level* aLevel, int health) : Tower(aLevel, TowerTypeBasic),
    m_Health(health)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	m_FasterTower = new OpenGLTexture("TileTower");
    m_Ammo = 1000;
}

FasterTower::~FasterTower()
{
    
}

void FasterTower::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_FasterTower, getX(), getY(), getWidth(), getHeight());
    
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}
}

const char* FasterTower::getType()
{
	return BASIC_TOWER_TYPE;
}

int FasterTower::getHealth()
{
	return m_Health;
}