#include "GameConstants.h"


//Game Constants
const char* GAME_SCREEN_NAME = "Game";

//Tiles Constants
const char* TILE_GROUND_TYPE = "GroundTile";
const char* TILE_TREE_TYPE = "TreeTile";
const char* TILE_CHEST_TYPE = "ChestTile";
const char* TILE_WALL_TYPE = "WallTile";
const char* TILE_WATER_TYPE = "WaterTile";
const char* TILE_SPAWN_HERO_TYPE = "HeroSpawn";
const char* TILE_SPAWN_ENEMY_TYPE = "EnemySpawn";
const char* TILE_TOWER_TYPE = "TowerTile";

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
const int ENEMY_COUNT = 1;

//Ammo Pickup constants

const char* AMMO_PICKUP_TYPE = "AmmoPickup";

//Tower constants
const char* BASIC_TOWER_TYPE = "BasicTower";
const char* FASTER_TOWER_TYPE = "FasterTower";
const int MAX_UPGRADE_LEVEL = 6;