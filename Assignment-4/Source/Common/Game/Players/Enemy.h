#ifndef ENEMY_H
#define ENEMY_H


#include "Player.h"


class OpenGLTexture;
class Hero;
class Tower;

class Enemy : public Player
{
public:
	Enemy(Level* level, float speed);
	~Enemy();

	const char * getType();
    
    void update(double delta);

	void paint();
	void reset();

protected:
	void handlePlayerCollision(Projectile* projectile);
    void randomDirection();

private:
	OpenGLTexture* m_Enemy;
	Hero* m_Hero;
    Tower** m_Towers;
};

#endif