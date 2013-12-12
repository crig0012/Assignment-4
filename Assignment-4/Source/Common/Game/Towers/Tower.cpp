//
//  Tower.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-05.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Tower.h"
#include "../Players/Hero.h"
#include "../Level.h"
#include "../../Game/Tiles/Tile.h"
#include "../../Input/Input.h"
#include "../../Utils/Utils.h"
#include "../Players/Enemy.h"
#include "../Projectiles.h"
#include "../../Constants/Constants.h"
#include "../../Math/GDRandomSearch.h"
#include "../../UI/UIFont.h"
#include <sstream>

Tower::Tower(Level* aLevel, TowerType towerType) : Player(aLevel),
    m_TowerType(towerType),
    m_Then(time(0)),
    m_UpgradeLevel(1)
{    
    m_Smoke1 = false;
    m_Smoke2 = false;
    m_Smoke3 = false;
    m_Smoke4 = false;
    
    m_Smoke = new UIFont("Smoke");
    m_IsSmoking = false;
    
    m_Explo1 = false;
    m_Explo2 = false;
    m_Explo3 = false;
    m_Explo4 = false;
    m_Explo5 = false;
    m_Explo6 = false;
    m_Explo7 = false;
    
    
    m_Explosion = new UIFont("Explosion");
    m_IsExploding = false;
}

Tower::~Tower()
{
    m_UpgradeLevel = 1;
}

bool Tower::getIsExploding()
{
    return m_IsExploding;
}

void Tower::upgradeTower()
{
    if(m_UpgradeLevel != MAX_UPGRADE_LEVEL)
    {
        m_UpgradeLevel++;
    }
}

std::string Tower::getUpgradeLevelStr()
{
    std::stringstream streamThing;
    streamThing << getUpgradeLevel();
    std::string lastStringThing = streamThing.str();
    
    return lastStringThing;
}

int Tower::getUpgradeLevel()
{
    return m_UpgradeLevel;
}

void Tower::update(double delta)
{
    if(m_Level->getIsEditing() == true)
        return;
    
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
        
        if(elapsedTime < (1/getUpgradeLevel()))
        {
            return;
        }
    
        if(m_EnemyArray.at(temp)->getIsActive() == false)
        {
            return;
        }
        
        if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_EnemyArray.at(temp)), 50 * getUpgradeLevel()))
        {
            Tile* targetTile = m_Level->getTileForPlayer(m_EnemyArray.at(temp));
            float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
            float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
            
            //Fire the projectiles
            fireProjectile(centerX, centerY);

            
            time(&m_Then);
        }
}

//OpenGLTexture* Tower::getTexture()
//{
    
//}

void Tower::paint()
{
    if(getTowerType() == TowerTypeBasic)
    
    OpenGLRenderer::getInstance()->drawTexture(m_TowerTexture, getX(), getY());
    
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}
}

void Tower::reset()
{
    setIsActive(false);
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
                
                if(enemy->getHealth() <= 0)
                {
                    GDRandom random;
                    random.randomizeSeed();
                    
                    PickupType types[] = {PickupTypeAmmo, PickupTypeCoin, PickupTypeHealth};
                    int index = random.random(3);
                    
                    m_Level->setPickupTypeAtIndex(types[index], m_Level->getTileIndexForPlayer(enemy));
                }
                
                //Apply damage to the enemy AND set the projectile to inactive
                enemy->applyDamage(projectile->getDamage() * getUpgradeLevel(), m_Level->getTileIndexForTile(enemyTile));
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

void Tower::explode()
{
    m_IsExploding = true;
    
    time(&m_NowExplode);

    int explosionTime = (m_NowExplode - m_ThenExplode);

    switch (explosionTime)
    {
    case 1:
        m_Explo7 = false;
        m_Explo1 = true;
        break;
        
    case 2:
        m_Explo1 = false;
        m_Explo2 = true;
        break;
        
    case 3:
        m_Explo2 = false;
        m_Explo3 = true;
        break;
        
    case 4:
        m_Explo3 = false;
        m_Explo4 = true;
        break;
        
    case 5:
        m_Explo4 = false;
        m_Explo5 = true;
        break;
        
    case 6:
        m_Explo5 = false;
        m_Explo6 = true;
        break;
        
    case 7:
        m_Explo6 = false;
        m_Explo7 = true;
        break;
        
    default:
        break;
    }

    if(m_Explo1 == true)
    {
        m_Explosion->setText("1");
        m_Explosion->draw(getX(), getY());
    }

    if(m_Explo2 == true)
    {
        m_Explosion->setText("2");
        m_Explosion->draw(getX(), getY());
    }

    if(m_Explo3 == true)
    {
        m_Explosion->setText("3");
        m_Explosion->draw(getX(), getY());
    }

    if(m_Explo4 == true)
    {
        m_Explosion->setText("4");
        m_Explosion->draw(getX(), getY());
    }
    
    if(m_Explo5 == true)
    {
        m_Explosion->setText("5");
        m_Explosion->draw(getX(), getY());
    }

    if(m_Explo6 == true)
    {
        m_Explosion->setText("6");
        m_Explosion->draw(getX(), getY());
    }

    if(m_Explo7 == true)
    {
        m_Explosion->setText("7");
        m_Explosion->draw(getX(), getY());
    
        time(&m_ThenExplode);
        m_IsExploding = false;
        m_IsSmoking = true;
        smoke();
    }
}

void Tower::smoke()
{
    m_IsExploding = true;
    
    time(&m_NowExplode);
    
    int explosionTime = (m_NowExplode - m_ThenExplode);
    
    switch (explosionTime)
    {
        case 1:
            m_Smoke4 = false;
            m_Smoke1 = true;
            break;
            
        case 2:
            m_Smoke1= false;
            m_Smoke2 = true;
            break;
            
        case 3:
            m_Smoke2 = false;
            m_Smoke3 = true;
            break;
            
        case 4:
            m_Smoke3 = false;
            m_Smoke4 = true;
            break;
            
        default:
            break;
    }
    
    if(m_Smoke1 == true)
    {
        m_Smoke->setText("1");
        m_Smoke->draw(getX(), getY());
    }
    
    if(m_Smoke2 == true)
    {
        m_Smoke->setText("2");
        m_Smoke->draw(getX(), getY());
    }
    
    if(m_Smoke3 == true)
    {
        m_Smoke->setText("3");
        m_Smoke->draw(getX(), getY());
    }
    
    if(m_Smoke4 == true)
    {
        m_Smoke->setText("4");
        m_Smoke->draw(getX(), getY());
    }
}

bool Tower::getIsSmoking()
{
    return m_IsSmoking;
}