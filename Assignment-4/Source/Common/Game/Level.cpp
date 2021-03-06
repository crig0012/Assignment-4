//
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Players/Player.h"
#include "Players/Hero.h"
#include "Players/Enemy.h"
#include "Pathfinder/PathFinder.h"
#include "Game.h"
#include "Pickups/Pickups.h"
#include "Pickups/AmmoPickup.h"
#include "Pickups/CoinPickup.h"
#include "Pickups/HealthPickup.h"
#include "Tiles/Tile.h"
#include "Tiles/TreeTile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/WallTile.h"
#include "Tiles/TowerTile.h"
#include "Tiles/ChestTile.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include <stdlib.h>
#include <fstream>
#include "../Utils/Logger/Logger.h"
#include "../Math/GDRandomSearch.h"
#include "../Game/Towers/Tower.h"
#include "Towers/BasicTower.h"
#include "Towers/FasterTower.h"
#include "../UI/UIFont.h"
#include <algorithm>
#include <sstream>
#include <time.h>


Level::Level(bool isEditingLevel) :
m_HorizontalTiles(0),
	m_VerticalTiles(0),
	m_TileSize(EMPTY_LEVEL_TILE_SIZE),
	m_PlayerStartingTileIndex(EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX),
	m_Hero(NULL),
	m_Tiles(NULL),
	m_SelectedTileIndex(-1),
	m_PaintTileScoring(false),
	m_PaintTileIndexes(false),
	m_Projectile(NULL),
	m_Pickup(NULL),
	m_TowerType(TowerTypeBasic),
    m_IsEditing(isEditingLevel),
    m_TimeToDraw(0),
    m_Difficulty(2)
{
	//Create the player object
	if(m_IsEditing == false)
	{
        m_Font = new UIFont("BitmapFont");
		//Create the hero object 
		m_Hero = new Hero(this);

		//TODO: Make constants for these
		float min = 50.0f;
		float max = PLAYER_SPEED - 25.0f;
		GDRandom random;
		random.randomizeSeed();

		//Create the enemy objects
		for(int i = 0; i < ENEMY_COUNT; i ++)
		{
			float speed = min + random.random(max-min);

			Enemy* enemy = new Enemy(this, speed);
			m_Enemies.push_back(enemy);
		}
	}
    
	//Calculate the number of horizontal and vertical tiles
	m_HorizontalTiles = ScreenManager::getInstance()->getScreenWidth() / m_TileSize;
	m_VerticalTiles = ScreenManager::getInstance()->getScreenHeight() / m_TileSize;

	//Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tiles = new Tile*[m_HorizontalTiles * m_VerticalTiles];

	//Initialize all the tiles to NULL
	for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
	{
		m_Tiles[i] = NULL;
	}

	//Load an empty level
	load(NULL);
}

Level::~Level()
{
	//Delete the player object
	if(m_Hero != NULL)
	{
		delete m_Hero;
		m_Hero = NULL;
	}

	//Delete the enemy objects
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		delete m_Enemies.at(i);
		m_Enemies.at(i) = NULL;
	}

	m_Enemies.clear();

	//Delete the tiles array, the inheriting class
	//must delete the object in this array itself
	if(m_Tiles != NULL)
	{
		//Cycle through and delete all the tile objects in the array
		for(int i = 0; i < getNumberOfTiles(); i++)
		{
			if(m_Tiles[i] != NULL)
			{
				delete m_Tiles[i];
				m_Tiles[i] = NULL;
			}
		}

		delete[] m_Tiles;
		m_Tiles = NULL;
	}
}

void Level::randomizeLevel()
{
	GDRandom random;
	random.randomizeSeed();

	TileType types[] = {TileTypeGround, TileTypeWater, TileTypeTree, TileTypeWall, TileTypeTower, TileTypeChest};
    //TODO: Add other tower types
	for( int i = 0; i < getNumberOfTiles(); i++)
	{
		int index = random.random(6);
        
        if(index == 5)
        {
            setTowerTypeAtIndex(TowerTypeBasic, index);
        }
        
		setTileTypeAtIndex(types[index], i);
	}
}

Tile** Level::getTiles()
{ 
    return m_Tiles;
}

bool Level::getIsEditing()
{
    return m_IsEditing;
}

void Level::update(double aDelta)
{
    if(m_Enemies.size() == 0)
    {
        ScreenManager::getInstance()->switchScreen(LEVEL_SELECT_MENU_SCREEN_NAME);
    }
    
	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->update(aDelta);
            
            if(m_Tiles[i]->getTower() != NULL)
            {
                if(m_Tiles[i]->getTower()->getIsExploding() == true)
                {
                    m_Tiles[i]->getTower()->explode();
                }
                
                if(m_Tiles[i]->getTower()->getIsSmoking() == true)
                {
                    m_Tiles[i]->getTower()->explode();
                }
            }
        }
	}

	//Update the Hero
	if(m_Hero != NULL)
	{
		m_Hero->update(aDelta);
	}

	//Update the enemy objects
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		if(m_Enemies.at(i)->getIsActive() == true)
		{
			m_Enemies.at(i)->update(aDelta);
            if(m_Enemies.at(i)->getPathFinder() == NULL)
            {
                Tile** m_Tiles = getTiles();
                
                GDRandom random;
                random.randomizeSeed();
                
                int min = 0;
                
                int max = sizeof(m_Towers);
                
                int towerToDestroy = random.random(max-min);
                
                m_Towers[towerToDestroy]->reset();
                delete m_Towers[i];
				m_Towers[i] = NULL;
                m_Tiles[i]->reset(); //TODO: See if this worked
            }
		}
	}

	for(int i = 0; i < m_Projectile.size(); i++)
	{
		if(m_Projectile.at(i)->getIsActive() == true)
		{
			m_Projectile.at(i)->update(aDelta);
		}
	}

	if(m_Pickup != NULL)
	{
		if(m_Pickup->getIsActive() == true)
		{
			m_Pickup->update(aDelta);
		}
	}
}

void Level::paint()
{   
	//Cycle through and paint all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		//Safety check the tile
		if(m_Tiles[i] != NULL)
		{
			//Paint the tile
			m_Tiles[i]->paint();

			//If the paint tile indexes flag is set to true,
			//draw the index number on the tiles
			if(m_PaintTileIndexes == true)
			{
				m_Tiles[i]->paintIndex(i);
			}
		}
	}

	//Paint the Player
	if(m_Hero != NULL)
	{
		//If paint tile scoring flag is set to true,
		//draw the path scoring
		if(m_PaintTileScoring == true)
		{
			m_Hero->getPathFinder()->paint();
		}

		//Paint the player
		m_Hero->paint();
	}

	//paint the enemies
	for(int i = 0; i < m_Enemies.size(); i++)
	{
		if(m_Enemies.at(i)->getIsActive() == true)
		{
			m_Enemies.at(i)->paint();
		}
	}

	for(int i = 0; i < m_Projectile.size(); i++)
	{
		if(m_Projectile.at(i)->getIsActive() == true)
		{
			m_Projectile.at(i)->paint();
		}
	}

	if(m_Pickup != NULL)
	{
		if(m_Pickup->getIsActive() == true)
		{
			m_Pickup->paint();
		}
	}
    
    if(m_IsEditing == true)
        return;
    
    //HUD  
    m_Font->setText(toConst("Lives: ", m_Hero->getLives()));
    m_Font->draw(50, 600);

    m_Font->setText(toConst("Health: ", m_Hero->getHealth()));
    m_Font->draw(350, 600);
    
	m_Font->setText(toConst("Ammo: ", m_Hero->getAmmo()));
    m_Font->draw(50, 650);

    m_Font->setText(toConst("Money: ", m_Hero->getMoney()));
    m_Font->draw(350, 650);

	m_Font->setText(toConst("Score: ", m_Hero->getScore()));
    m_Font->draw(50, 700);
	//TODO: Make this work
    
     time(&m_Now);
     float elapsedTime = m_Now - m_Then;
    
     m_Font->setText(toConst("Time: ", m_TimeToDraw));
     m_Font->draw(350, 700);
    
     if(elapsedTime < 1)
     {
        return;
     }
    
     m_TimeToDraw++;
    
     time(&m_Then);
}

void Level::setTime()
{
    time(&m_Start);
}

void Level::setDifficulty(int difficulty)
{
    m_Difficulty = difficulty;
}

int Level::getDifficulty()
{
    return m_Difficulty;
}

const char* Level::toConst(std::string stringToChange, int intToChange)
{
    std::string stringThing = stringToChange;
    int intThing = intToChange;
    
    std::stringstream streamThing;
    streamThing << intThing;
    std::string lastStringThing = streamThing.str();
    
    stringThing += lastStringThing;
    
    const char* final = stringThing.c_str();
    
    return final;
}

void Level::reset()
{
	//Random number generator for the spawn indexes
	GDRandom random;
	random.randomizeSeed();
	int tileIndex = -1;
	std::vector<int> usedTileIndexes;

	// set tileIndex to - 1
	tileIndex = - 1;

	while (tileIndex == - 1)
	{
		tileIndex = random.random(getNumberOfTiles());

		//Safety check that it is a walkable tile
		if(getTileForIndex(tileIndex)->isWalkableTile() == false)
		{
			tileIndex = - 1;
		}
		else
		{
			//Cycle through and ensure the index hasnt already been used
			for(int j = 0; j < usedTileIndexes.size(); j++)
			{
				if(usedTileIndexes.at(j) == tileIndex)
				{
					tileIndex = - 1;
					break;
				}
			}
		}
	}



	//Cycle through and reset all the tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->reset();
		}
	}

	// make a player* vector to hold the hero and enemies for reset()
	std::vector<Enemy*> enemies;

	for(int i = 0; i < m_Enemies.size(); i++)
	{
		enemies.push_back(m_Enemies.at(i));
	}

	//Set the enemy spawn at the top left corner(first tile)
	for(int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->setCurrentTile(getTileForIndex(0));
		m_Hero->setCurrentTile(getTileForIndex(tileIndex));
		enemies.at(i)->reset();
		m_Hero->reset();
	}
}

void Level::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	setMouseCoordinates(positionX, positionY);

	if(m_Hero != NULL)
	{
		m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}

	//Convert the mouse click position, into a tile index
	int index = getTileIndexForPosition(positionX, positionY);
	//Set the selected tile index
	setSelectedTileIndex(index);

	//If the tile is walkable, set the player's destination tile
	if(m_Tiles[index]->isWalkableTile() == true)
	{
		if(m_Hero != NULL)
		{
			m_Tiles[index]->setIsSelected(true);
			m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
		}
	}
}

void Level::setMouseCoordinates(float positionX, float positionY)
{
	m_MouseX = positionX / m_TileSize;
	m_MouseY = positionY / m_TileSize;
}

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	if(m_Hero->getIsActive() == false)
		return;

	//Convert the mouse click position, into a tile index
	int index = getTileIndexForPosition(aPositionX, aPositionY);

	//Safety check that the tile isn't NULL
	if(m_Tiles[index] != NULL)
	{
		//Set the selected tile index
		setSelectedTileIndex(index);

		//If the tile is walkable, set the player's destination tile
		if(m_Tiles[index]->isWalkableTile() == true)    //Change this to false later, I only want towers on non walkable areas
		{
			setTowerTypeAtPosition(m_TowerType, aPositionX, aPositionY);
		}
	}
}

void Level::setTowerType(TowerType towerType)
{
	m_TowerType = towerType;
}

void Level::keyDownEvent(int keyCode)
{
	if(keyCode == KEYCODE_W)
	{
		int coordinateX = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getX());
		int coordinateY = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getY() - 1);


		Tile* newTile = getTileForCoordinates(coordinateX, coordinateY);

		m_Hero->setDestinationTile(newTile);
	}
	else if(keyCode == KEYCODE_S)
	{
		int coordinateX = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getX());
		int coordinateY = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getY()) + 1;


		Tile* newTile = getTileForCoordinates(coordinateX, coordinateY);

		m_Hero->setDestinationTile(newTile);
	}
	else if(keyCode == KEYCODE_A)
	{
		int coordinateX = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getX() - 1);
		int coordinateY = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getY());


		Tile* newTile = getTileForCoordinates(coordinateX, coordinateY);

		m_Hero->setDestinationTile(newTile);
	}
	else if(keyCode == KEYCODE_D)
	{
		int coordinateX = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getX()) + 1;
		int coordinateY = getTileCoordinateForPosition(getTileForPlayer(m_Hero)->getY());


		Tile* newTile = getTileForCoordinates(coordinateX, coordinateY);

		m_Hero->setDestinationTile(newTile);
	}
}

void Level::keyUpEvent(int keyCode)
{
    if(keyCode == KEYCODE_O)
    {
        m_Hero->setSpeed(PLAYER_SPEED * 5);
        for(int i = 0; i < m_Enemies.size(); i++)
        {
            m_Enemies.at(i)->setSpeed(PLAYER_SPEED * 5);
        }
    }
    else if(keyCode == KEYCODE_K)
    {
        m_Hero->setSpeed(PLAYER_SPEED);
        for(int i = 0; i < m_Enemies.size(); i++)
        {
            m_Enemies.at(i)->setSpeed(PLAYER_SPEED);
        }
    }
    else if(keyCode == KEYCODE_M)
    {
        m_Hero->setSpeed(PLAYER_SPEED / 5);
        for(int i = 0; i < m_Enemies.size(); i++)
        {
            m_Enemies.at(i)->setSpeed(PLAYER_SPEED / 5);
        }
    }
	else if(keyCode == KEYCODE_1)
	{
		setTowerType(TowerTypeBasic);
	}
	else if(keyCode == KEYCODE_2)
	{
		setTowerType(TowerTypeFaster);
	}
	else if(keyCode == KEYCODE_R)
	{
		reset();
	}
    else if(keyCode == KEYCODE_B)
    {
        for(int i = 0; i < getNumberOfTiles(); i++)
        {
            if(m_Tiles[i] != NULL)
            {
                if(m_Tiles[i]->getTower() != NULL)
                {
                    m_Tiles[i]->getTower()->explode();
                }
            }
        }
    }
	else if(keyCode == KEYCODE_I)
	{
		togglePaintTileIndexes();
	}
	else if(keyCode == KEYCODE_Q)
	{
		togglePaintTileScoring();
	}
	else if(keyCode == KEYCODE_F)
	{
		m_Hero->getPathFinder()->togglePathFindingDelay();
	}
	else if(keyCode == KEYCODE_P)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_MENU_SCREEN_NAME);
	}
	else if(keyCode == KEYCODE_U)
	{
		int index = getTileIndexForCoordinates(m_MouseX, m_MouseY);

		if(m_Tiles[index] != NULL)
		{
            if (m_Tiles[index]->getTower() != NULL)
            {
                m_Tiles[index]->getTower()->upgradeTower();
            }
		}

	}
	else
	{
		if(m_Hero != NULL)
		{
			m_Hero->keyUpEvent(keyCode);
		}
	}
}

void Level::load(const char* levelName)
{
	//TODO: Fix the load
	//TODO: Also, when you quit the game theres an exception, and doesnt stop debuggin
	if(levelName != NULL)
	{
		std::ifstream inputStream;

        // open the file
		inputStream.open(levelName, std::ifstream::in | std::ifstream::binary);

		//Unlike the output stream, if the input stream doesnt find the file, the input stream
		//wont create it, and is_open will return false
		if(inputStream.is_open() == true)
		{
			//determine how many bytes are in the file
			inputStream.seekg(0, inputStream.end);
			long long levelSize = inputStream.tellg();

			//seek back to the start of the file for reading
			inputStream.seekg(0, inputStream.beg);

			//create a buffer for our data
			char* buffer = new char[levelSize];

			//Read the data from input stream into our buffer
			inputStream.read(buffer, (int)levelSize);

			//close the input stream
			inputStream.close();

			// let's validate our buffer data
			for(int i = 0; i < levelSize; i++)
			{
				PickupType pickupType = PickupTypeUnknown;
                TowerType towerType = TowerTypeUnknown;

				//Check to see if the Buuffer[i] contains the AmmoPickup bit
				if((buffer[i] & PickupTypeAmmo) > 0)
				{
					//It does
					pickupType = PickupTypeAmmo;

					//Clear the AmmoPickup bit
					buffer[i] &= ~PickupTypeAmmo;
				}

                if((buffer[i] & PickupTypeCoin) > 0)
				{
					//It does
					pickupType = PickupTypeCoin;
                    
					//Clear the AmmoPickup bit
					buffer[i] &= ~PickupTypeCoin;
				}
                
                if((buffer[i] & PickupTypeHealth) > 0)
				{
					//It does
					pickupType = PickupTypeHealth;
                    
					//Clear the AmmoPickup bit
					buffer[i] &= ~PickupTypeHealth;
				}
                
                if((buffer[i] & TowerTypeBasic) > 0)
				{
					//It does
					towerType = TowerTypeBasic;
                    
					//Clear the AmmoPickup bit
					buffer[i] &= ~TowerTypeBasic;
				}
                
                //Set the tile type
				setTileTypeAtIndex((TileType)buffer[i], i);

				//Set the Pickup type
				setPickupTypeAtIndex(pickupType, i);
                
                //Set the Tower type
                setTowerTypeAtIndex(towerType, i);
			}

			//Delete the buffer, it was allocated on the heap after all
			delete[] buffer;
			buffer = NULL;
		}
	}
	else
	{
		//Tile variables
		int tileIndex = 0;
		float tileX = 0.0f;
		float tileY = 0.0f;

		//Cycle through all the tiles and create them
		for(int v = 0; v < getNumberOfVerticalTiles(); v++)
		{
			for(int h = 0; h < getNumberOfHorizontalTiles(); h++)
			{
				//The empty level will contain only ground tiles
				m_Tiles[tileIndex] = new GroundTile();
				m_Tiles[tileIndex]->setPosition(tileX, tileY);
				m_Tiles[tileIndex]->setSize(m_TileSize, m_TileSize);

				//Increment the tile index
				tileIndex++;

				//And increment the tile x position
				tileX += m_TileSize;
			}

			//Increment the tile y position and reset the tile x position, since we started a new row
			tileY += m_TileSize;
			tileX = 0.0f;
		}
	}

	//The level is loaded, reset everything
	reset();
}

void Level::save(const char* levelName)
{
	//TODO: save the level

	int bufferSize = getNumberOfTiles();
	char* Buffer = new char[bufferSize];

	//Create the buffer
	for( int i = 0; i < bufferSize; i++)
	{
		Buffer[i] = (char)getTileTypeForIndex(i);

		//Save the tile's pickup if there is one
		if(m_Tiles[i]->getPickup() != NULL && m_Tiles[i]->getPickup()->getPickupType() != PickupTypeUnknown)
		{
			Buffer[i] |= m_Tiles[i]->getPickup()->getPickupType();
		}
        
        if(m_Tiles[i]->getTower() != NULL && m_Tiles[i]->getTower()->getTowerType() != TowerTypeUnknown)
		{
			Buffer[i] |= m_Tiles[i]->getTower()->getTowerType();
		}
	}

	//File IO time
	std::ofstream outputStream;

	//Open the file
	outputStream.open(levelName, std::ofstream::out | std::ofstream::binary);

	//Did the file open?
	if(outputStream.is_open() == true)
	{
		//Write the buffer
		outputStream.write(Buffer, bufferSize);

		//Make sure to close the file stream
		outputStream.close();
	}
	else
	{
		//This may be a place where you could throw an exception in your game,
		//if you are opening a file for reading OR writing and it doesn't open.
	}

	//Delete the buffer, it was allocated on the heap after all
	delete[] Buffer;
	Buffer = NULL;

}

TileType Level::getTileTypeForIndex(int index)
{
	if(index >= 0 && index < getNumberOfTiles())
	{
		return m_Tiles[index]->getTileType();
	}
	return TileTypeUnknown;
}

PickupType Level::getPickupTypeForIndex(int index)
{
	if(index >= 0 && index < getNumberOfTiles())
	{
		if(m_Tiles[index]->getPickup() != NULL)
		{
			return m_Tiles[index]->getPickup()->getPickupType();
		}
	}
	return PickupTypeUnknown;
}

unsigned int Level::getNumberOfTiles()
{
	return getNumberOfHorizontalTiles() * getNumberOfVerticalTiles();
}

unsigned int Level::getNumberOfHorizontalTiles()
{
	return m_HorizontalTiles;
}

unsigned int Level::getNumberOfVerticalTiles()
{
	return m_VerticalTiles;
}

bool Level::validateTileCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	if(aCoordinatesX < 0 || aCoordinatesY < 0 || aCoordinatesX >= getNumberOfHorizontalTiles() || aCoordinatesY >= getNumberOfVerticalTiles())
	{
		return false;
	}
	return true;
}

int Level::getTileCoordinateForPosition(int aPosition)
{
	return (aPosition / m_TileSize);
}

int Level::getTileIndexForPosition(int aPositionX, int aPositionY)
{
	int coordinatesX = getTileCoordinateForPosition(aPositionX);
	int coordinatesY = getTileCoordinateForPosition(aPositionY);
	return getTileIndexForCoordinates(coordinatesX, coordinatesY);
}

int Level::getTileIndexForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	//Validate the coordinates, then calculate the array index
	if(validateTileCoordinates(aCoordinatesX, aCoordinatesY) == true)
	{
		return aCoordinatesX + (aCoordinatesY * getNumberOfHorizontalTiles());
	}

	return -1;
}

int Level::getTileIndexForTile(Tile* aTile)
{
	return getTileIndexForPosition(aTile->getX(), aTile->getY());
}

int Level::getTileIndexForTower(Tower* tower)
{
    if(tower != NULL)
        return getTileIndexForPosition(tower->getX(), tower->getY());
    else
        return 0;
}

int Level::getTileIndexForPlayer(Player* player)
{
	return getTileIndexForPosition(player->getX(), player->getY());
}

Tile* Level::getTileForPosition(int aPositionX, int aPositionY)
{
	return getTileForIndex(getTileIndexForPosition(aPositionX, aPositionY));
}

Tile* Level::getTileForCoordinates(int aCoordinatesX, int aCoordinatesY)
{
	return getTileForIndex(getTileIndexForCoordinates(aCoordinatesX, aCoordinatesY));
}

Tile* Level::getTileForIndex(int aIndex)
{
	//Safety check the index bounds
	if(aIndex >= 0 && aIndex < getNumberOfTiles())
	{
		return m_Tiles[aIndex];
	}

	//If we got here, it means the index passed in was out of bounds
	return NULL;
}

Tile* Level::getTileForPlayer(Player* player)
{
	if(player != NULL)
		return getTileForPosition(player->getX(), player->getY());
    else return NULL;
}

void Level::setTileTypeAtPosition(TileType tileType, int positionX, int positionY)
{
	setTileTypeAtIndex(tileType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTileTypeAtCoordinates(TileType tileType, int coordinatesX, int coordinatesY)
{
	setTileTypeAtIndex(tileType, getTileIndexForCoordinates(coordinatesX, coordinatesY));
}

void Level::setTileTypeAtIndex(TileType tileType, int index)
{
	//Safety check the index
	if(index >= 0 && index < getNumberOfTiles())
	{
		//Don't replace the tile if its the same type of tile that already exists
		if(m_Tiles[index]->getTileType() == tileType)
		{
			return;
		}

		//Delete the tile at the index, if one exists
		if(m_Tiles[index] != NULL)
		{
			delete m_Tiles[index];
			m_Tiles[index] = NULL;
		}

		//Create the new tile based on the TileType
		switch (tileType)
		{
		case TileTypeGround:
			m_Tiles[index] = new GroundTile();
			break;

		case TileTypeWater:
			m_Tiles[index] = new WaterTile();
			break;

		case TileTypeTree:
			m_Tiles[index] = new TreeTile();
			break;

		case TileTypeWall:
			m_Tiles[index] = new WallTile();
			break;

		case TileTypeTower:
			m_Tiles[index] = new TowerTile();
			break;

		case TileTypeChest:
			m_Tiles[index] = new ChestTile();
			break;

        case TileTypeSpawnEnemy:
             m_Tiles[index] = new ChestTile();
             break;

        case TileTypeSpawnHero:
             m_Tiles[index] = new ChestTile();
             break;
                
		case TileTypeUnknown:
		default:
			m_Tiles[index] = NULL;
			break;
		}

		//Calculate the coordinates and set the tile position and size
		int coordinateX = (index % getNumberOfHorizontalTiles());
		int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
		m_Tiles[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
		m_Tiles[index]->setSize(m_TileSize, m_TileSize);
	}
}

void Level::setTowerTypeAtPosition(TowerType towerType, int positionX, int positionY)
{
	setTowerTypeAtIndex(towerType, getTileIndexForPosition(positionX, positionY));
}

void Level::setTowerTypeAtIndex(TowerType towerType, int index)
{
    //TODO: Right now towers are four squares big and in the top left corner
	//Safety check the index
	if(index >= 0 && index < getNumberOfTiles())
	{
		//Don't replace the tile if its the same type of tile that already exists
		if(m_Tiles[index] != NULL && m_Tiles[index]->getTower() != NULL)
        {
            if(m_Tiles[index]->getTower()->getTowerType() == towerType)
            {
                return;
            }
        }
		//Create the new tile based on the TileType
		switch (towerType)
		{
		case TowerTypeBasic:
			m_Tiles[index]->setTower(new BasicTower(this, 5));
            //m_Towers[index] = new BasicTower(this, 5);
			break;
                
        case TowerTypeFaster:
            m_Tiles[index]->setTower(new FasterTower(this, 2));
            //m_Towers[index] = new FasterTower(this, 2);
            break;
                
        case TowerTypeUnknown:
            break;
		}

		//Set the pickups position and size
        if(m_Tiles[index]->getTower() != NULL)
        {
            int coordinateX = (index % getNumberOfHorizontalTiles());
            int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
            
            Tower* tower = m_Tiles[index]->getTower();
            float x = (coordinateX * m_TileSize) + (m_TileSize - tower->getWidth()) / 2.0f;
            float y = (coordinateY * m_TileSize) + (m_TileSize - tower->getHeight()) / 2.0f;
            tower->setPosition(x, y);
        }
    }
}

void Level::setPickupTypeAtPosition(PickupType pickupType, int positionX, int positionY)
{
	setPickupTypeAtIndex(pickupType, getTileIndexForPosition(positionX, positionY));
}

void Level::setPickupTypeAtCoordinates(PickupType pickupType, int coordinateX, int coordinateY)
{
	setPickupTypeAtIndex(pickupType, getTileIndexForCoordinates(coordinateX, coordinateY));
}

void Level::setPickupTypeAtIndex(PickupType pickupType, int index)
{
	//Safety check the index
	if(index >= 0 && index < getNumberOfTiles())
	{
		//Don't replace the tile if a pick up of the same type already exists there
		if(m_Tiles[index] != NULL && m_Tiles[index]->getPickup() != NULL)
		{
			if(m_Tiles[index]->getPickup()->getPickupType() == pickupType)
			{
				return;
			}
		}

		//Delete the pickup at the index, if one exists already
		if(m_Tiles[index] != NULL)
		{
			if(m_Tiles[index]->getPickup() != NULL)
			{
				m_Tiles[index]->setPickup(NULL);
			}

			//Create a new pickup object based on the PickupType
			switch(pickupType)
			{
                case PickupTypeAmmo:
				{
					GDRandom random;
					random.randomizeSeed();

					int min = 1;
					int max = 5;
					int ammo = min + random.random(max-min);

					m_Tiles[index]->setPickup(new AmmoPickup(ammo));
				}
				break;

                case PickupTypeCoin:
				{
					GDRandom random;
					random.randomizeSeed();
                    
					int min = 1;
					int max = 3;
					int coin = min + random.random(max-min);
                    
					m_Tiles[index]->setPickup(new CoinPickup(coin));
				}
                break;
                    
                case PickupTypeHealth:
				{
					GDRandom random;
					random.randomizeSeed();
                    
					int min = 1;
					int max = 3;
					int health = min + random.random(max-min);
                    
					m_Tiles[index]->setPickup(new HealthPickup(health));
				}
                break;
                    
				//TODO: Make sure to add future pickups here for object creation

			case PickupTypeUnknown:
			default:
				break;
			}

			//Set the pickups position and size
			if(m_Tiles[index]->getPickup() != NULL)
			{
				int coordinateX = (index % getNumberOfHorizontalTiles());
				int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());

				Pickup* pickup = m_Tiles[index]->getPickup();
				float x = (coordinateX * m_TileSize) + (m_TileSize - pickup->getWidth()) / 2.0f;
				float y = (coordinateY * m_TileSize) + (m_TileSize - pickup->getHeight()) / 2.0f;
				pickup->setPosition(x, y);
			}

		}

	}
}

void Level::togglePaintTileScoring()
{
	m_PaintTileScoring = !m_PaintTileScoring;
}

void Level::togglePaintTileIndexes()
{
	m_PaintTileIndexes = !m_PaintTileIndexes;
}

void Level::setSelectedTileIndex(int aSelectedIndex)
{
	//Deselect the previously selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(false);
	}

	//Set the new tile index
	m_SelectedTileIndex = aSelectedIndex;

	//Selected the newly selected tile
	if(m_SelectedTileIndex >= 0 && m_SelectedTileIndex < getNumberOfTiles())
	{
		m_Tiles[m_SelectedTileIndex]->setIsSelected(true);
	}
}

int Level::getSelectedTileIndex()
{
	return m_SelectedTileIndex;
}

Hero* Level::getHero()
{
	return m_Hero;
}

std::vector<Enemy*> Level::getEnemies()
{
	return m_Enemies;
}
