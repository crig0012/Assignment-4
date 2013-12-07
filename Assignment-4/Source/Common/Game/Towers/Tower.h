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
#include "Player.h"
#include "../../Constants/Constants.h"
#include "Projectiles.h"
#include <vector>

class Enemy;
class Player;

class Tower : public Player
{
public:
	Tower(Level* aLevel, TowerType towerType);
	virtual ~Tower();

	virtual void update(double delta);
	virtual void paint() = 0;
	virtual void reset();

	virtual const char* getType() = 0;

	virtual TowerType getTowerType();

protected:
    void handlePlayerCollision(Projectile* projectile);
    void handleBoundsCollision(Projectile* projectile);
    TowerType m_TowerType;
    
private:
    std::vector<Enemy*> m_EnemyArray;
    
};

#endif /* defined(__GAM_1514_OSX_Game__Tower__) */