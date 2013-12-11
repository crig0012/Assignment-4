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
    void update(double delta);

	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void keyUpEvent(int keyCode);
	void mouseLeftClickUpEvent(float positionX, float positionY);
    
    void plusScore();
    int getScore();

protected:
	void handlePlayerCollision(Projectile* projectile);
	OpenGLTexture* m_Player;
    int m_Score;
    int m_ScoreToLifeTracker;
};

#endif