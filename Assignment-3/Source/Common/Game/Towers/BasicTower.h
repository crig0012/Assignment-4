



#include "Tower.h"

class OpenGLTexture;

class BasicTower : public Tower
{
public:
	BasicTower(int health);
	~BasicTower();

	void paint();

	const char* getType();

	int getHealth();

private:
	int m_Health;
	OpenGLTexture* m_BasicTower;
};
