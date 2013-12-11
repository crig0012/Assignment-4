#include "Projectiles.h"
#include "../Utils/Utils.h"
#include <math.h>

Projectile::Projectile(ProjectileListener* listener, int damage, float velocity) : GameObject(),
	m_Listener(listener),
	m_Damage(damage),
	m_Velocity(velocity * 100),
	m_Angle(0.0f),
	m_TargetX(0.0f),
	m_TargetY(0.0f)
{

}

Projectile::~Projectile()
{
    
}

void Projectile::update(double delta)
{
	//Calculate the position of the projectile based on the velocity and angle
	float x = getX() + m_Velocity * cosf(m_Angle) * delta;
	float y = getY() + m_Velocity * sinf(m_Angle) * delta;
	setPosition(x, y);

	//Handle the player and bounds collision
	if(m_Listener != NULL)
	{
		m_Listener->handlePlayerCollision(this);
		m_Listener->handleBoundsCollision(this);
	}
}

void Projectile::paint()
{
	OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
	OpenGLRenderer::getInstance()->setPointSize(5.0f);
	OpenGLRenderer::getInstance()->drawCircle(getX(), getY(), 5.0f, 5.0f);
	OpenGLRenderer::getInstance()->setPointSize(1.0f);
}

void Projectile::reset()
{

}

const char* Projectile::getType()
{
	//TODO: Makea constant for this
	return "Projectile";
}

void Projectile::setTarget(float x, float y)
{
	//set the target
	m_TargetX = x;
	m_TargetY = y;

	//Calculate the angle (int radians)
	float deltaX = m_TargetX - getX();
	float deltaY = m_TargetY - getY();
	float angleInDegrees = atan2f(deltaY, deltaX) * 180 / M_PI;
	m_Angle = MathUtils::degressToRadians(angleInDegrees);
}

int Projectile::getDamage()
{
	return m_Damage;
}

