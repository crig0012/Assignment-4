//
//  Tower.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-05.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Tower.h"
#include "Hero.h"
#include "Level.h"
#include "../../Game/Tiles/Tile.h"
#include "../../Input/Input.h"
#include "../../Utils/Utils.h"
#include "Enemy.h"
#include "Projectiles.h"
#include "Constants.h"
#include "../../Math/GDRandomSearch.h"

Tower::Tower(Level* aLevel, TowerType towerType) : Player(aLevel),
    m_TowerType(towerType),
    m_Then(time(0))
{

}

Tower::~Tower()
{
    
}

void Tower::upgradeTower()
{
    if(m_UpgradeLevel != MAX_UPGRADE_LEVEL)
    {
        m_UpgradeLevel++;
    }
}

int Tower::getUpgradeLevel()
{
    return m_UpgradeLevel;
}

void Tower::update(double delta)
{
    time(&m_Now);
    float elapsedTime = m_Now - m_Then;
    
    MathUtils mathUtils;
    m_EnemyArray = m_Level->getEnemies();
    
    //Update the projectiles
    for(int i = 0; i < m_Projectiles.size(); i++)
    {
        if(m_Projectiles.at(i)->getIsActive() == true)
        {
            m_Projectiles.at(i)->update(delta);
        }
    }
    
    //Remove any inactive projectiles from the projectiles vector
    int index = 0;
    while(index != m_Projectiles.size())
    {
        if(m_Projectiles.at(index)->getIsActive() == false)
        {
            Log::debug("Deleting projectile");
            
            //delete the projectile and remove it from the vector
            delete m_Projectiles.at(index);
            m_Projectiles.erase(m_Projectiles.begin() + index);
        }
        
        else
        {
            index++;
        }
    }
    
    //for(int i = 0; i < m_EnemyArray.size(); i++)
    //{
        GDRandom random;
        random.randomizeSeed();
    
        std::vector<int> usedEnemies;

        int temp = -1;
        
        while (temp == - 1)
		{
			temp = random.random(m_EnemyArray.size());
			
            //Cycle through and ensure the index hasnt already been used
            for(int j = 0; j < usedEnemies.size(); j++)
            {
                if(usedEnemies.at(j) == temp)
                {
                    temp = - 1;
                    break;
                }
            }
        }
        
        if(elapsedTime < 1)
        {
            return;
        }
        
        if(m_EnemyArray.at(temp)->getIsActive() == false)
        {
            return;
        }
        
        if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_EnemyArray.at(temp)), 600))
        {
            Tile* targetTile = m_Level->getTileForPlayer(m_EnemyArray.at(temp));
            float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
            float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
            
            //Fire the projectiles
            fireProjectile(centerX, centerY);

            
            time(&m_Then);
            
            //break;
            //usleep(1000000);
        }
    //}
}

void Tower::paint()
{
    OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorGreen());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, 90);
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2, 90, false);
}

void Tower::reset()
{
    
}

TowerType Tower::getTowerType()
{
    return m_TowerType;
}

void Tower::handlePlayerCollision(Projectile *projectile)
{
    Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
    
    //Cycle through all the enemies and check for collision with the projectile
    for(int i = 0; i < m_Level->getEnemies().size(); i++)
    {
        Enemy* enemy = m_Level->getEnemies().at(i);
        if(enemy != NULL && enemy->getIsActive() == true)
        {
            //Get the tile the enemy is on
            Tile* enemyTile = m_Level->getTileForPlayer(enemy);
            
            //Is the projectile on the same tile as the enemy?
            if(tile == enemyTile)
            {
                Log::debug("Tower projectile hit an enemy at index %i", i);
                
                if(m_Level != NULL)
                {
                    m_Level->setPickupTypeAtIndex(PickupTypeAmmo, m_Level->getTileIndexForPlayer(enemy));
                }
                
                //Apply damage to the enemy AND set the projectile to inactive
                enemy->applyDamage(projectile->getDamage());
                projectile->setIsActive(false);
            }
        }
    }
}

void Tower::handleBoundsCollision(Projectile* projectile)
{
    Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
    if(tile == NULL)
    {
        projectile->setIsActive(false);
    }
}