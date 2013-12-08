#include "GameConstants.h"


//Game Constants
const char* GAME_SCREEN_NAME = "Game";

//Tiles Constants
const char* TILE_GROUND_TYPE = "GroundTile";
const char* TILE_GRASS_TYPE = "GrassTile";
const char* TILE_WATER_TYPE = "WaterTile";
const char* TILE_ROCK_TYPE = "RockTile";
const char* TILE_HOLE_TYPE = "HoleTile";
const char* TILE_TREE_TYPE = "TreeTile";
const char* TILE_CORE_TYPE = "CoreTile";

const int TILE_PADDING = 2;

//Player Constants
const int PLAYER_SIZE = 24;
const float PLAYER_SPEED = 150.0f;
const OpenGLColor PLAYER_INSIDE_COLOR = OpenGLColor(0.0f, 0.0f, 0.0f, 1.0f);
const OpenGLColor PLAYER_OUTLINE_COLOR = OpenGLColor(1.0f, 1.0f, 1.0f, 1.0f);

//Hero Constants
const char* HERO_TYPE = "Hero";

//Enemy Constants
const char* ENEMY_TYPE = "Enemy";
const int ENEMY_COUNT = 10;

//Ammo Pickup constants

const char* AMMO_PICKUP_TYPE = "AmmoPickup";

//Tower constants
const char* BASIC_TOWER_TYPE = "BasicTower";
const int MAX_UPGRADE_LEVEL = 4;