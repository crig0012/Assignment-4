//
//  Tower.h
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-05.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__Tower__
#define __GAM_1514_OSX_Game__Tower__


#include "../GameObject.h"
#include "../Players/Player.h"
#include "../../Constants/Constants.h"
#include "../Projectiles.h"
#include <vector>
#include <time.h>

class Enemy;
class Player;
class UIFont;

class Tower : public Player
{
public:
	Tower(Level* aLevel, TowerType towerType);
	virtual ~Tower();
    
    void explode();

	virtual void update(double delta);
	virtual void paint();
	virtual void reset();

	virtual const char* getType() = 0;

	virtual TowerType getTowerType();
    
    virtual void upgradeTower();
    virtual int getUpgradeLevel();
    
    bool getIsExploding();

protected:
    void handlePlayerCollision(Projectile* projectile);
    void handleBoundsCollision(Projectile* projectile);
    TowerType m_TowerType;
    OpenGLTexture* m_TowerTexture;
    
private:
    std::vector<Enemy*> m_EnemyArray;
    int m_UpgradeLevel;
    int m_FireRate;
    
    UIFont* m_Explosion;
    
    time_t m_Then;
    time_t m_Now;
    
    bool m_Explo1;
    bool m_Explo2;
    bool m_Explo3;
    bool m_Explo4;
    bool m_Explo5;
    bool m_Explo6;
    bool m_Explo7;
    
    bool m_IsExploding;
    
    time_t m_ThenExplode;
    time_t m_NowExplode;
    
    void setTime();
};

#endif /* defined(__GAM_1514_OSX_Game__Tower__) */