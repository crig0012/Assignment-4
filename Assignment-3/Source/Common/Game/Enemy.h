#ifndef ENEMY_H
#define ENEMY_H



#include "Player.h"


class OpenGLTexture;
class Hero;

class Enemy : public Player
{
public:
	Enemy(Level* level, float speed);
	virtual ~Enemy();

	const char * getType();

	void update(double delta);
	void paint();
	void reset();

protected:
	void handlePlayerCollision(Projectile* projectile);

private:
	Tile* m_Tile;
	Hero* m_Hero;
	OpenGLTexture* m_Bush;
};

#endif