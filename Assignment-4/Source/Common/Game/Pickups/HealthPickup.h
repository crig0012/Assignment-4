//
//  HealthPickup.h
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-12.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__HealthPickup__
#define __GAM_1514_OSX_Game__HealthPickup__

#include "Pickups.h"

class HealthPickup : public Pickup
{
public:
	HealthPickup(int healthCount);
	~HealthPickup();
    
	const char* getType();
    
	int getHealthCount();
    
private:
	int m_HealthCount;
};

#endif /* defined(__GAM_1514_OSX_Game__HealthPickup__) */
