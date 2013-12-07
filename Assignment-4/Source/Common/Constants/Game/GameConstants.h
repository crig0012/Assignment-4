#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;

//Tile Constants
extern const char* TILE_GROUND_TYPE;
extern const char* TILE_GRASS_TYPE;
extern const char* TILE_WATER_TYPE;
extern const char* TILE_ROCK_TYPE;
extern const char* TILE_HOLE_TYPE;
extern const char* TILE_TREE_TYPE;
extern const char* TILE_CORE_TYPE;

extern const int TILE_PADDING;

//Player Constants
extern const int PLAYER_SIZE;
extern const float PLAYER_SPEED;
extern const OpenGLColor PLAYER_INSIDE_COLOR;
extern const OpenGLColor PLAYER_OUTLINE_COLOR;

//Hero Constants
extern const char* HERO_TYPE;

//Enemy Constants
extern const char* ENEMY_TYPE;
extern const int ENEMY_COUNT;

//Pickup constants
extern const char* AMMO_PICKUP_TYPE;

//Tower constants
extern const char* BASIC_TOWER_TYPE;

#endif 