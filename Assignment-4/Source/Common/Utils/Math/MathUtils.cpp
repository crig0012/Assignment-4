//
//  MathUtils.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MathUtils.h"
#include <math.h>
#include <stdlib.h>
#include "../../Game/Level.h"
#include "../../Game/Tiles/Tile.h"

unsigned int MathUtils::nextPowerOf2(unsigned int aValue)
{
    //Determine the power of 2 for the parameter
    unsigned int powerOf2 = 4;
    while(powerOf2 < aValue)
    {
        powerOf2 <<= 1;
    }
    
    return powerOf2;
}

float MathUtils::radiansToDegrees(float aRadians)
{
    return aRadians * (180.0f / M_PI);
}

float MathUtils::degressToRadians(float aDegrees)
{
    return aDegrees * (M_PI / 180.0f);
}

bool MathUtils::withinRange(Level* level, float valueA, float valueB, float range)
{
    if(level == NULL || valueA == NULL || valueB == NULL || range == 0)
        return false;
    
    Tile* tileA = level->getTileForIndex(valueA);
    Tile* tileB = level->getTileForIndex(valueB);
    
    float centerXA = tileA->getX() + (tileA->getWidth() / 2.0f);
    float centerYA = tileA->getY() + (tileA->getHeight() / 2.0f);
    
    float centerXB = tileB->getX() + (tileB->getWidth() / 2.0f);
    float centerYB = tileB->getY() + (tileB->getHeight() / 2.0f);
    
    float squaredX = (centerXB - centerXA) * (centerXB - centerXA);
    float squaredY = (centerYB - centerYA) * (centerYB - centerYA);
    
    float distance = sqrtf(squaredX + squaredY);
    
    return fabsf(distance) < range;
}