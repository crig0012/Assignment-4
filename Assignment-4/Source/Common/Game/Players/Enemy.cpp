#include "Enemy.h"
#include "../Level.h"
#include "../Tiles/Tile.h"
#include "Hero.h"
#include "../../Utils/Utils.h"
#include "../../Constants/Constants.h"
#include "../../OpenGL/OpenGL.h"
#include "../../Math/GDRandom.h"
#include "../Towers/Tower.h"


Enemy::Enemy(Level* level, float speed) : Player(level),
    m_Hero(m_Level->getHero())
{
	m_Speed = speed;
    m_Lives = 1;
    m_Health = 1;

	m_Enemy = new OpenGLTexture("Enemy"); //TODO: Make one for the enemy and player
}

Enemy::~Enemy()
{
	if(m_Enemy != NULL)
	{
		delete m_Enemy;
		m_Enemy = NULL;
	}
}

const char* Enemy::getType()
{
	return ENEMY_TYPE;
}

void Enemy::update(double delta)
{
    MathUtils mathUtils;
    Player::update(delta);
    GDRandom random;
    random.randomizeSeed();
    
    /*m_Towers = m_Level->getTowers();
    
    int min = 0;
    int max = sizeof(m_Towers);
    int towerToHunt = random.random(max-min);
    
    if(m_Hero == NULL || m_Hero->getIsActive() == false)
    {
        m_Level->getHero();
        return;
    }
  
    if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForTower(m_Towers[towerToHunt]), 300))
    {
        if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForTower(m_Towers[towerToHunt]), 100))
        {
            randomDirection();
            return;
        }
        
        Player::setDestinationTile(m_Level->getTileForIndex(m_Level->getTileIndexForTower(m_Towers[towerToHunt])));
    }*/
    
    if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_Hero), 300))
    {
        if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_Hero), 100))
        {
            randomDirection();
            return;
        }
        
        Player::setDestinationTile(m_Level->getTileForPlayer(m_Hero));
    }
    
    else
    {
        randomDirection();
    }
    
    time(&m_Now);
    float elapsedTime = m_Now - m_Then;    
    
    if(elapsedTime < 3)
    {
        return;
    }
    
    if(mathUtils.withinRange(m_Level, m_Level->getTileIndexForPlayer(this), m_Level->getTileIndexForPlayer(m_Hero), 105))
    {
        Tile* targetTile = m_Level->getTileForPlayer(m_Hero);
        float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
        float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);
        
        //Fire the projectiles
        fireProjectile(centerX, centerY);
        
        time(&m_Then);
    }
}

void Enemy::randomDirection()
{
    GDRandom random;
    random.randomizeSeed();
    
    int wayToGo = random.random(4);
    
    int coordinateX = m_Level->getTileCoordinateForPosition(m_Level->getTileForPlayer(this)->getX());
    int coordinateY = m_Level->getTileCoordinateForPosition(m_Level->getTileForPlayer(this)->getY());
    
    switch (wayToGo)
    {
        case 0:
            Player::setDestinationTile(m_Level->getTileForCoordinates(coordinateX, coordinateY - 1));
            break;
            
        case 1:
            Player::setDestinationTile(m_Level->getTileForCoordinates(coordinateX, coordinateY + 1));
            break;
            
        case 2:
            Player::setDestinationTile(m_Level->getTileForCoordinates(coordinateX - 1, coordinateY));
            break;
            
        case 3:
            Player::setDestinationTile(m_Level->getTileForCoordinates(coordinateX + 1, coordinateY));
            break;
            
        default:
            break;
    }
}

void Enemy::paint()
{
	OpenGLRenderer::getInstance()->drawTexture(m_Enemy, getX(), getY(), getWidth(), getHeight());
    
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}																														
	}
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
				Log::debug("Enemy damaged the player");

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
				Log::debug("Enemy projectile hit the hero");
                
				//Apply damage to the enemy and set the projectile to inactive
				m_Hero->applyDamage(projectile->getDamage(), m_Level->getTileIndexForTile(tileProjectile));
				projectile->setIsActive(false);
			}
		
	}
}