#ifndef HERO_H
#define HERO_H


class OpenGLTexture;


#include "Player.h"


class Hero : public Player
{
public:
	Hero(Level* level);
	~Hero();

	const char * getType();

	void paint();

	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void keyUpEvent(int keyCode);
	void mouseLeftClickUpEvent(float positionX, float positionY);

protected:
	void handlePlayerCollision(Projectile* projectile);
	OpenGLTexture* m_Player;
};

#endif