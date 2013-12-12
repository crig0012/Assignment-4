#include "Pickups.h"


Pickup::Pickup(PickupType pickupType)
{

}

Pickup::~Pickup()
{

}

void Pickup::update(double delta)
{

}

void Pickup::paint()
{
    OpenGLRenderer::getInstance()->drawTexture(m_PickupTexture, getX(), getY());
}

void Pickup::reset()
{

}

PickupType Pickup::getPickupType()
{
	return m_PickupType;
}