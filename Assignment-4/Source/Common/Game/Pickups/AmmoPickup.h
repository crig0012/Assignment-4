#ifndef AMMOPICKUP_H
#define AMMOPICKUP_H

#include "Pickups.h"

class AmmoPickup : public Pickup
{
public:
	AmmoPickup(int ammoCount);
	~AmmoPickup();

	const char* getType();

	int getAmmoCount();

private:
	int m_AmmoCount;
};

#endif