//
//  CoinPickup.h
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__CoinPickup__
#define __GAM_1514_OSX_Game__CoinPickup__

#include "Pickups.h"

class CoinPickup : public Pickup
{
public:
	CoinPickup(int coinCount);
	~CoinPickup();
    
	const char* getType();
    
	int getCoinCount();
    
private:
	int m_CoinCount;
};

#endif /* defined(__GAM_1514_OSX_Game__CoinPickup__) */
