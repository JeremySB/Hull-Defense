// Created by Jeremy Bost

#pragma once
#include "tower.h"

namespace photonCannonNS {
	const int PRICE = 500;
	const float RANGE = 300.0f;
	const float PROJECTILE_DURATION = 0.12f; // in seconds
	const float TIME_BETWEEN_SHOTS = 1;//0.3f; // in seconds
	const float ROTATE_SPEED = 0.5f; // radians per second
	const int STARTING_HEALTH = 600;
	const int DAMAGE = 50;
	const float GUN_FRAME_DELAY = 0.08f;
	const int GUN_FRAME_START = 0;
	const int GUN_FRAME_END = 4;
}

class PhotonCannon : public Tower
{
public:
	PhotonCannon();
	~PhotonCannon();

	virtual void attackTarget(Entity* target);

	virtual float getRange() { return towerNS::RANGE; }

	virtual void setProjectileTexture(TextureManager* tm);
	virtual void setGunTexture(TextureManager* tm);

	virtual void repair() { health = towerNS::STARTING_HEALTH; }
};

