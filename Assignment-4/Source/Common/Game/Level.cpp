//
//  Level.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "Level.h"
#include "Player.h"
#include "Hero.h"
#include "Enemy.h"
#include "PathFinder.h"
#include "Game.h"
#include "Pickups/Pickups.h"
#include "Pickups/AmmoPickup.h"
#include "Tiles/Tile.h"
#include "Tiles/GroundTile.h"
#include "Tiles/GrassTile.h"
#include "Tiles/WaterTile.h"
#include "Tiles/RockTile.h"
#include "Tiles/HoleTile.h"
#include "Tiles/TreeTile.h"
#include "../Constants/Constants.h"
#include "../Input/Input.h"
#include "../Screen Manager/ScreenManager.h"
#include <stdlib.h>
#include <fstream>
#include "../Utils/Logger/Logger.h"
#include "../Math/GDRandomSearch.h"
#include "../Game/Towers/Tower.h"
#include "BasicTower.h"


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
    m_TowerType(TowerTypeBasic)
{
    //Create the player object
    if(isEditingLevel == false)
    {
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
    
    //Allocate the tiles array, the inheriting class will populate this array with Tile objects
	m_Tower = new Tower*[m_HorizontalTiles * m_VerticalTiles];
    
    //Initialize all the tiles to NULL
    for(int i = 0; i < m_HorizontalTiles * m_VerticalTiles; i++)
    {
        m_Tower[i] = NULL;
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


//Delete the tower array, the inheriting class
//must delete the object in this array itself
if(m_Tower != NULL)
{
    //Cycle through and delete all the tower objects in the array
    for(int i = 0; i < getNumberOfTiles(); i++)  // MAKE A getNumberOfTowers() function
    {
        if(m_Tower[i] != NULL)
        {
            delete m_Tower[i];
            m_Tower[i] = NULL;
        }
    }
    
    delete[] m_Tower;
    m_Tower = NULL;
}
}


void Level::update(double aDelta)
{
	//Update all the game tiles
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tiles[i] != NULL)
		{
			m_Tiles[i]->update(aDelta);
		}
	}
    
    //Update all the game towers
	for(int i = 0; i < getNumberOfTiles(); i++) // MAKE A getNumberOfTowers() function
	{
		if(m_Tower[i] != NULL)
		{
			m_Tower[i]->update(aDelta);
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
    
    //Cycle through and paint all the towers
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
        //Safety check the tower
		if(m_Tower[i] != NULL)
		{
            //Paint the tile
            m_Tower[i]->paint();
            
            //If the paint tile indexes flag is set to true,
            //draw the index number on the towers
            if(m_PaintTileIndexes == true)
            {
                m_Tower[i]->paint();
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
    
    //Cycle through and reset all the towers
	for(int i = 0; i < getNumberOfTiles(); i++)
	{
		if(m_Tower[i] != NULL)
		{
			m_Tower[i]->reset();
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


	////Random number generator for the spawn indexes
	//GDRandom random;
	//random.randomizeSeed();
	//int tileIndex = -1;
	//std::vector<int> usedTileIndexes;

	////Cycle through the Player objects
	//for(int i = 0; i < players.size(); i++)
	//{
	//	// set tileIndex to - 1
	//	tileIndex = - 1;

	//	while (tileIndex == - 1)
	//	{
	//		tileIndex = random.random(getNumberOfTiles());

	//		//Safety check that it is a walkable tile
	//		if(getTileForIndex(tileIndex)->isWalkableTile() == false)
	//		{
	//			tileIndex = - 1;
	//		}
	//		else
	//		{
	//			//Cycle through and ensure the index hasnt already been used
	//			for(int j = 0; j < usedTileIndexes.size(); j++)
	//			{
	//				if(usedTileIndexes.at(j) == tileIndex)
	//				{
	//					tileIndex = - 1;
	//					break;
	//				}
	//			}

	//			//Safety check that tileIndex isn't - 1
	//			if(tileIndex != -1)
	//			{
	//				players.at(i)->setCurrentTile(getTileForIndex(tileIndex));
	//				players.at(i)->reset();
	//				usedTileIndexes.push_back(tileIndex);
	//			}
	//		}
	//	}
	//}
}

void Level::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
	if(m_Hero != NULL)
	{
		m_Hero->mouseMovementEvent(deltaX, deltaY, positionX, positionY);
	}




	//Convert the mouse click position, into a tile index
	int index = getTileIndexForPosition(positionX, positionY);
    
	//

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

void Level::mouseLeftClickUpEvent(float aPositionX, float aPositionY)
{
	////Convert the mouse click position, into a tile index
	//int index = getTileIndexForPosition(aPositionX, aPositionY);

	////Safety check that the tile isn't NULL
	//if(m_Tiles[index] != NULL)
	//{
	//	TowerType types[] = {TowerTypeBasic};
	//	TowerType type = types[m_SelectedTileIndex];
 //       setTowerTypeAtPosition(type, aPositionX, aPositionY);
	//}



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
            /*if(m_Hero != NULL)
            {
                m_Hero->mouseLeftClickUpEvent(aPositionX, aPositionY);
            }*/

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
    if(keyCode == KEYCODE_R)
    {
        reset();
    }
    else if(keyCode == KEYCODE_I)
    {
        togglePaintTileIndexes();
    }
	else if(keyCode == KEYCODE_Q)
	{
		togglePaintTileScoring();
	}
	else if(keyCode == KEYCODE_E)
	{
		m_Hero->getPathFinder()->togglePathFindingDelay();
	}
	else if(keyCode == KEYCODE_P)
	{
		ScreenManager::getInstance()->switchScreen(PAUSE_MENU_SCREEN_NAME);
	}
    else if(keyCode == KEYCODE_0)
    {
        setTowerType(TowerTypeBasic);
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
		long long bufferSize = inputStream.tellg();

		//seek back to the start of the file for reading
		inputStream.seekg(0, inputStream.beg);

		//create a buffer for our data
		char* buffer = new char[bufferSize];

		//Read the data from input stream into our buffer
		inputStream.read(buffer, (int)bufferSize);

		//close the input stream 
		inputStream.close();

		// let's validate our buffer data
		for(int i = 0; i < bufferSize; i++)
		{
			PickupType pickupType = PickupTypeUnknown;

			//Check to see if the Buuffer[i] contains the AmmoPickup bit
			if((buffer[i] & PickupTypeAmmo) > 0)
			{
				//It does
				pickupType = PickupTypeAmmo;

				//Clear the AmmoPickup bit
				buffer[i] &= ~PickupTypeAmmo;
			}

			//Set the tile type
			setTileTypeAtIndex((TileType)buffer[i], i);

			//Set the Pickup type
			setPickupTypeAtIndex(pickupType, i);
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
	char* Buuffer = new char[bufferSize];

	//Create the buffer
	for( int i = 0; i < bufferSize; i++)
	{
		 Buuffer[i] = (char)getTileTypeForIndex(i);

		 //Save the tile's pickup if there is one
		 if(m_Tiles[i]->getPickup() != NULL && m_Tiles[i]->getPickup()->getPickupType() != PickupTypeUnknown)
		 {
			 Buuffer[i] |= m_Tiles[i]->getPickup()->getPickupType();
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
        outputStream.write(Buuffer, bufferSize);
        
        //Make sure to close the file stream
        outputStream.close();
    }
    else
    {
        //This may be a place where you could throw an exception in your game,
        //if you are opening a file for reading OR writing and it doesn't open.
    }
    
	//Delete the buffer, it was allocated on the heap after all
	delete[] Buuffer;
	Buuffer = NULL;

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
	return getTileForPosition(player->getX(), player->getY());
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

			case TileTypeGrass:
				m_Tiles[index] = new GrassTile();
                break;

			case TileTypeWater:
				m_Tiles[index] = new WaterTile();
                break;

			case TileTypeRock:
				m_Tiles[index] = new RockTile();
                break;

			case TileTypeHole:
				m_Tiles[index] = new HoleTile();
                break;

			case TileTypeTree:
				m_Tiles[index] = new TreeTile();
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
    //Safety check the index
    if(index >= 0 && index < getNumberOfTiles())
	{
        //Don't replace the tile if its the same type of tile that already exists
        if(m_Tower[index] != NULL && m_Tower[index]->getTowerType() == towerType)
        {
            return;
        }
        
        //Create the new tile based on the TileType
        switch (towerType)
        {
            case TowerTypeBasic:
                m_Tower[index] = new BasicTower(this, 3);
                break;
        }
        
        //Calculate the coordinates and set the tile position and size
        int coordinateX = (index % getNumberOfHorizontalTiles());
        int coordinateY = ((index - coordinateX) / getNumberOfHorizontalTiles());
        m_Tower[index]->setPosition(coordinateX  * m_TileSize, coordinateY * m_TileSize);
        m_Tower[index]->setSize(m_TileSize, m_TileSize);
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

					int min = 5;
					int max = 50;
					int ammo = min + random.random(max-min);

					m_Tiles[index]->setPickup(new AmmoPickup(ammo));
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
