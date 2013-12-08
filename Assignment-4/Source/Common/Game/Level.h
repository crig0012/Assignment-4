//
//  Level.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "../Constants/Constants.h"
#include <vector>


class Tile;
class CoreTile;
class Player;
class Hero;
class Enemy;
class Pickup;
class Projectile;
class Tower;

class Level
{
public:
	Level(bool isEditingLevel = false);
	~Level();
    
	//Update, paint and reset methods
	void update(double delta);
    void paint();
    void reset();
    
    //
    void load(const char* levelName);
    void save(const char* levelName);
    
    //Input methods
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    void mouseLeftClickUpEvent(float positionX, float positionY);
    void keyUpEvent(int keyCode);
    void keyDownEvent(int keyCode);
	
	//
    TileType getTileTypeForIndex(int index);
	PickupType getPickupTypeForIndex(int index);
    
	//Tile count methods
    unsigned int getNumberOfTiles();
	unsigned int getNumberOfHorizontalTiles();
	unsigned int getNumberOfVerticalTiles();
    
	//Validate that the tile coordinates passed in are valid
	bool validateTileCoordinates(int coordinatesX, int coordinatesY);
    
	//Converts a position in screen space into a position in coordinate space
	int getTileCoordinateForPosition(int position);
    
	//Index methods
	int getTileIndexForPosition(int positionX, int positionY);
	int getTileIndexForCoordinates(int coordinatesX, int coordinatesY);
	int getTileIndexForTile(Tile* tile);
	int getTileIndexForPlayer(Player* player);
    
	//Tile methods
	Tile* getTileForPosition(int positionX, int positionY);
	Tile* getTileForCoordinates(int coordinatesX, int coordinatesY);
	Tile* getTileForIndex(int index);
	Tile* getTileForPlayer(Player* player);
	Tile* getTileForCore(CoreTile* core);
    
    //
    void setTileTypeAtPosition(TileType tileType, int positionX, int positionY);
    void setTileTypeAtCoordinates(TileType tileType, int coordinateX, int coordinateY);
    void setTileTypeAtIndex(TileType tileType, int index);

	void setTowerTypeAtPosition(TowerType towerType, int positionX, int positionY);
	void setTowerTypeAtIndex(TowerType towerType, int index);
    void setTowerType(TowerType towerType);

	//
	void setPickupTypeAtPosition(PickupType pickupType, int positionX, int positionY);
	void setPickupTypeAtCoordinates(PickupType pickType, int coordinateX, int coordinateY);
	void setPickupTypeAtIndex(PickupType pickupType, int index);
    
    //Coveniance methods to toggle debug paint methods
    void togglePaintTileScoring();
    void togglePaintTileIndexes();

	void getTileType();

		//Disables the old tiles selection (if ground tile) and
	//enables the newly selected tiles selection (if ground tile)
	void setSelectedTileIndex(int selectedIndex);
	int getSelectedTileIndex();

	//Getter method for the hero*
	Hero* getHero();
	std::vector<Enemy*> getEnemies();
    
protected:
   
	//Protected Member variables
	Hero* m_Hero;
	std::vector<Enemy*> m_Enemies;
	Tile** m_Tiles;
	Tower** m_Tower;
    std::vector<Projectile*> m_Projectile;
	Pickup* m_Pickup;
	unsigned int m_HorizontalTiles;
	unsigned int m_VerticalTiles;
	unsigned int m_TileSize;
    unsigned int m_PlayerStartingTileIndex;
    TowerType m_TowerType;
	int m_SelectedTileIndex;
    bool m_PaintTileScoring;
    bool m_PaintTileIndexes;
};

#endif
