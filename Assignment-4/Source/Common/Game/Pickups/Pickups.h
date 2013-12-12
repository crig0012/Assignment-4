#ifndef PICKUPS_H
#define PICKUPS_H

#include "../GameObject.h"
#include "../../Constants/Constants.h"
#include "../../OpenGL/OpenGLTexture.h"

class Pickup : public GameObject
{
public:
	Pickup(PickupType pickupType);
	virtual ~Pickup();

	virtual void update(double delta);
	virtual void paint();
	virtual void reset();

	virtual const char* getType() = 0;

	virtual PickupType getPickupType();

protected:
	PickupType m_PickupType;
	OpenGLTexture* m_PickupTexture;
};

#endif