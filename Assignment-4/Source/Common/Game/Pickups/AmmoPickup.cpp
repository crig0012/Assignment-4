#include "AmmoPickup.h"

AmmoPickup::AmmoPickup(int ammoCount) : Pickup(PickupTypeAmmo),
	m_AmmoCount(ammoCount)
{
	//TODO: The size should be that of the texture
	//you use for the ammo pick (or any pick)
	setSize(24.0f, 24.0f);
	m_PickupTexture = new OpenGLTexture("AmmoV2");
	
}

AmmoPickup::~AmmoPickup()
{

}

const char* AmmoPickup::getType()
{
	return AMMO_PICKUP_TYPE;
}

int AmmoPickup::getAmmoCount()
{
	return m_AmmoCount;
}