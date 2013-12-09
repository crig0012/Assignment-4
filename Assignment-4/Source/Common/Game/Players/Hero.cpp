







#include "Hero.h"
#include "Level.h"
#include "../Tiles/Tile.h"
#include "../../Constants/Constants.h"
#include "../../Input/Input.h"
#include "../../Utils/Utils.h"
#include "Enemy.h"
#include "../../OpenGL/OpenGL.h"


Hero::Hero(Level* level) : Player(level)
{
	m_Player = new OpenGLTexture("Player");
    m_Health = 3;
}

Hero::~Hero()
{
	if(m_Player != NULL)
	{
		delete m_Player;
		m_Player = NULL;
	}
}

const char* Hero::getType()
{
	return HERO_TYPE;
}

void Hero::paint()
{
    for(int i = 0; i < m_Projectiles.size(); i++)
	{
		if(m_Projectiles.at(i)->getIsActive() == true)
		{
			m_Projectiles.at(i)->paint();
		}
	}
    
	OpenGLRenderer::getInstance()->drawTexture(m_Player, getX() - 2.5, getY() - 2.5, getWidth() + 5, getHeight() + 5);
}

void Hero::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	Tile* tile = m_Level->getTileForPosition(positionX, positionY);
	if(tile != NULL && tile->isWalkableTile() == true)
	{
		//Set the level's selected tile, this call is optional, don't put it
		//in if you don't want the red retical to show up
		m_Level->setSelectedTileIndex(m_Level->getTileIndexForTile(tile));
	}
	
}

void Hero::update(double delta)
{
    if(m_IsActive == false)
        return;
    Player::update(delta);
}

void Hero::mouseLeftClickUpEvent(float positionX, float positionY)
{
	Tile* tile = m_Level->getTileForPosition(positionX, positionY);
	if(tile != NULL && tile->isWalkableTile() == true)
	{
		//Set the destination tile
		setDestinationTile(tile);
	}
}

void Hero::keyUpEvent(int keyCode)
{
    if(m_IsActive == false)
        return;
    
	if(keyCode == KEYCODE_SPACE)
	{
		Tile* targetTile = m_Level->getTileForIndex(m_Level->getSelectedTileIndex());
		float centerX = targetTile->getX() + (targetTile->getWidth() / 2.0f);
		float centerY = targetTile->getY() + (targetTile->getHeight() / 2.0f);

		//Fire the missles!
		fireProjectile(centerX, centerY);
	}
}

void Hero::handlePlayerCollision(Projectile* projectile)
{
	Tile* tile = m_Level->getTileForPosition(projectile->getX(), projectile->getY());

	//Cycle through all the enemies and check for collision with the projectile
	for(int i = 0; i < m_Level->getEnemies().size(); i++)
	{
		Enemy* enemy = m_Level->getEnemies().at(i);
		if(enemy != NULL && enemy->getIsActive() == true)
		{
			//Get the tile the enemy is on
			Tile* enemyTile = m_Level->getTileForPlayer(enemy);

			//Is the projectile on the same tile as the enemy?
			if(tile == enemyTile)
			{
				Log::debug("Hero projecttile hit an enemy");

				//Apply damage to the enemy and set the projectile to inactive
				enemy->applyDamage(projectile->getDamage());
				projectile->setIsActive(false);
			}
		}
	}
}