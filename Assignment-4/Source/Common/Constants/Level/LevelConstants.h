//
//  LevelConstants.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef LEVEL_CONSTANTS_H
#define LEVEL_CONSTANTS_H

//Global enum for the Level's tile types,
//add additional tile types in this enum
enum TileType
{
  TileTypeSpawnHero = 3,
  TileTypeSpawnEnemy = 5,
    
  TileTypeGround = 1, //  (0000 0001)
  TileTypeWater = 2, //   (0000 0010)
  TileTypeTree = 4, //   (0000 0100)
  TileTypeWall = 8, //    (0000 1000)
  TileTypeTower = 16, //   (0001 0000)
  TileTypeChest = 32, //   (0010 0000)
  TileTypeFasterTower = 64,

  //This count value must now be manually
  //updated when a new tile type is added
    
    TileTypeUnknown = -1,
    TileTypeCount = 7
};

enum PickupType
{
	PickupTypeAmmo = 128, // (1000 0000)
    PickupTypeCoin = 256,
    PickupTypeHealth = 512,

	//This count value must now be manually
    //updated when a new Pickup type is added
	PickupTypeCount = 3,
	PickupTypeUnknown = -1
};

enum TowerType
{
	TowerTypeBasic = 1024,
    TowerTypeFaster = 2048,
    
    TowerTypeUnknown = -1
};

//Level editor screen name
extern const char* LEVEL_EDITOR_SCREEN_NAME;
extern const char* SETTINGS_SCREEN_NAME;
extern const char* SAVE_SCREEN_NAME;
extern const char* LOAD_SCREEN_NAME;

//Empty Level Constants
extern const int EMPTY_LEVEL_TILE_SIZE;
extern const int EMPTY_LEVEL_STARTING_PLAYER_TILE_INDEX;

#endif
