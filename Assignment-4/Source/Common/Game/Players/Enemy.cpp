




#include "Enemy.h"
#include "../Level.h"
#include "../Tiles/Tile.h"
#include "Hero.h"
#include "../../Utils/Utils.h"
#include "../../Constants/Constants.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Math/GDRandom.h"


Enemy::Enemy(Level* level, float speed) : Player(level),
    m_Hero(m_Level->getHero())
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
    
    if(m_Hero == NULL || m_Hero->getIsActive() == false)
    {
        m_Level->getHero();
        return;
    }
    
    Player::setDestinationTile(m_Level->getTileForPlayer(m_Hero));
    
    time(&m_Now);
    float elapsedTime = m_Now - m_Then;
    
    MathUtils mathUtils;
    
    if(elapsedTime < 3)
    {
        return;
    }
    
    if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_Hero), 600))
    {
        Tile* targetTile = m_Level->getTileForPlayer(m_Hero);
        float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
        float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
        
        //Fire the projectiles
        fireProjectile(centerX, centerY);
        
        time(&m_Then);
    }
}

void Enemy::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_Bush, getX(), getY(), getWidth(), getHeight());
    
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}
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
    Tile* hero = m_Level->getTileForPlayer(m_Hero);

	for(int i = 0; i < m_Level->getEnemies().size(); i++)
	{
		Enemy* enemy = m_Level->getEnemies().at(i);
		if(enemy != NULL && enemy->getIsActive() == true)
		{
			//Get the tile the enemy is on
			Tile* enemyPosition = m_Level->getTileForPlayer(enemy);

			if(hero == enemyPosition)
			{
				Log::debug("Enemy damaged the OIL reserve");

				enemy->setIsActive(false);
			}
		}
	}
    
    Tile* tileProjectile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());
    
	//Cycle through all the enemies and check for collision with the projectile
	for(int i = 0; i < m_Level->getEnemies().size(); i++)
	{
			//Is the projectile on the same tile as the enemy?
			if(tileProjectile == hero)
			{
				Log::debug("Enemy projecttile hit an enemy");
                
				//Apply damage to the enemy and set the projectile to inactive
				m_Hero->applyDamage(projectile->getDamage());
				projectile->setIsActive(false);
			}
		
	}
}