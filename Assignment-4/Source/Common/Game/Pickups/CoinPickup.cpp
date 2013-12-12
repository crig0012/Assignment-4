//
//  CoinPickup.cpp
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "CoinPickup.h"

CoinPickup::CoinPickup(int coinCount) : Pickup(PickupTypeAmmo),
    m_CoinCount(coinCount)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	setSize(24.0f, 24.0f);
	m_PickupTexture = new OpenGLTexture("Coin");
	
}

CoinPickup::~CoinPickup()
{
    
}

const char* CoinPickup::getType()
{
	return COIN_PICKUP_TYPE;
}

int CoinPickup::getCoinCount()
{
	return m_CoinCount;
}