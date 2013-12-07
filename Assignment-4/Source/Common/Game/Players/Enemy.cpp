




#include "Enemy.h"
#include "Level.h"
#include "../Tiles/Tile.h"
#include "Hero.h"
#include "../../Utils/Utils.h"
#include "../../Constants/Constants.h"
#include "../../OpenGL/OpenGL.h"


Enemy::Enemy(Level* level, float speed) : Player(level)
{
	m_Speed = speed;

	m_Bush = new OpenGLTexture("BushFace");
}

Enemy::~Enemy()
{
	if(m_Bush != NULL)
	{
		delete m_Bush;
		m_Bush = NULL;
	}
}

const char* Enemy::getType()
{
	return ENEMY_TYPE;
}

void Enemy::update(double delta)
{
	Player::update(delta);

	//Set the destination tile based on the players current tile
	setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
}

void Enemy::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_Bush, getX(), getY(), getWidth(), getHeight());
	/*OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorRed());
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2 );
	OpenGLRenderer::getInstance()->setForegroundColor(PLAYER_OUTLINE_COLOR);
	OpenGLRenderer::getInstance()->drawCircle(getX() + (getWidth() / 2), getY() + (getHeight() / 2), getWidth() / 2 , false);*/
}

void Enemy::reset()
{
	Player::reset();

	//Set the destination tile
	setDestinationTile(m_Level->getTileForPlayer(m_Level->getHero()));
}

void Enemy::handlePlayerCollision(Projectile* projectile)
{
	Tile* heroFace = m_Level->getTileForPlayer(m_Level->getHero());

	for(int i = 0; i < m_Level->getEnemies().size(); i++)
	{
		Enemy* enemyFace = m_Level->getEnemies().at(i);
		if(enemyFace != NULL && enemyFace->getIsActive() == true)
		{
			//Get the tile the enemy is on
			Tile* enemyPosition = m_Level->getTileForPlayer(enemyFace);

			if(heroFace == enemyPosition)
			{
				Log::debug("Enemy damaged the OIL reserve");

				enemyFace->setIsActive(false);
			}
		}
	}
}