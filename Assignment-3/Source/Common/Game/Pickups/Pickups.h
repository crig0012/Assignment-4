#ifndef PICKUPS_H
#define PICKUPS_H



#include "../GameObject.h"
#include "../../Constants/Constants.h"


class Pickup : public GameObject
{
public:
	Pickup(PickupType pickupType);
	virtual ~Pickup();

	virtual void update(double delta);
	virtual void paint() = 0;
	virtual void reset();

	virtual const char* getType() = 0;

	virtual PickupType getPickupType();

protected:
	PickupType m_PickupType;
};

#endif