//
//  HealthPickup.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "HealthPickup.h"

HealthPickup::HealthPickup(int healthCount) : Pickup(PickupTypeAmmo),
    m_HealthCount(healthCount)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	setSize(24.0f, 24.0f);
	m_PickupTexture = new OpenGLTexture("Health");
	
}

HealthPickup::~HealthPickup()
{
    
}

const char* HealthPickup::getType()
{
	return HEALTH_PICKUP_TYPE;
}

int HealthPickup::getHealthCount()
{
	return m_HealthCount;
}