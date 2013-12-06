#pragma once

#include "../GameObject.h"
#include "../../Constants/Constants.h"


class Tower : public GameObject
{
public:
	Tower(TowerType towerType);
	virtual ~Tower();

	virtual void update(double delta);
	virtual void paint() = 0;
	virtual void reset();

	virtual const char* getType() = 0;

	virtual TowerType getTowerType();

protected:
	TowerType m_TowerType;
};