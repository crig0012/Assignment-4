//
//  FasterTower.h
//  GAM-1514 OSX Game
//
//  Created by Joel Cright on 2013-12-11.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__FasterTower__
#define __GAM_1514_OSX_Game__FasterTower__

#include "Tower.h"

class OpenGLTexture;

class FasterTower : public Tower
{
public:
	FasterTower(Level* aLevel, int health);
	~FasterTower();
    
	void paint();
    
	const char* getType();
    
	int getHealth();
    
private:
	int m_Health;
	OpenGLTexture* m_FasterTower;
};

#endif /* defined(__GAM_1514_OSX_Game__FasterTower__) */
