#include "turret.h"



Turret::Turret()
{
	setCollisionRadius(turretNS::RANGE);
}


Turret::~Turret()
{
}

bool Turret::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	
	return Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
}

void Turret::update(float frameTime)
{
	Entity::update(frameTime);
	
}

void Turret::attackTarget(Entity* target)
{

}
