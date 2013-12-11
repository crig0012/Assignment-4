//
//  Player.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObject.h"
#include "../Pathfinder/PathFinder.h"
#include "../Projectiles.h"
#include <vector>
#include <time.h>

class Level;
class Tile;
class Pickup;
class Hero;
class Enemy;

class Player : public GameObject, public PathFinderListener, public ProjectileListener
{
public:
	Player(Level* level);
	virtual ~Player();

  //Update, paint and reset methods
	void update(double delta);
	void paint();
	void reset();
  
  //keep GameObject's pure virtual method, we dont need to reclare it pure, but
  //it makes it easier for inheriting classes to know that Player is abstract.
  virtual const char* getType() = 0;
  
  //Setter methods for the current and destination tiles
	void setCurrentTile(Tile* tile);
	void setDestinationTile(Tile* tile);

	//Projectile methods
	void fireProjectile(float x, float y);
	void applyDamage(int damage, int index);
    
    int getLives();
	int getAmmo();

protected:
	//Projectile listener methods
	virtual void handlePlayerCollision(Projectile* projectile) = 0;
	virtual void handleBoundsCollision(Projectile* projectile);


	//Pickup method
	void handlePickup(Pickup* pickup);


	//PathFinder Listener Method
	void pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound);

	//Pathfinder methods
	PathFinder* getPathFinder();
	void findPath();

    //Speed methods
    float getSpeed();
    void setSpeed(float speed);

  //Animation methods
  float animate(float current, float target, double delta, float speed);
	void startAnimating();
	void stopAnimating();
  bool isAnimating();

  //Friend class Level so that it can access the protected members
  friend class Level;

	//Now the member variables are protected and can be accessed by inheriting classes
	Level* m_Level;
	PathFinder* m_PathFinder;
	Tile* m_CurrentTile;
	Tile* m_DestinationTile;
	Tile* m_Tile;
	bool m_CanAnimate;
    bool m_AbortAnimation;
	int m_AnimationPathNodeIndex;
	float m_Speed;
	int m_Ammo;
    time_t m_Now;
    time_t m_Then;
	int m_Health;
	std::vector<Projectile*> m_Projectiles;
    int m_Lives;
    std::vector<Enemy*> m_EnemyArray;
    
};

#endif