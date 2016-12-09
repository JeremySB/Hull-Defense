// Created by Jeremy Bost

#pragma once
#include "tower.h"
#include "enemy.h"

namespace photonCannonNS {
	const int PRICE = 500;
	const float RANGE = 300.0f;
	const float PROJECTILE_DURATION = 0.12f; // in seconds
	const float TIME_BETWEEN_SHOTS = 1;//0.3f; // in seconds
	const float ROTATE_SPEED = 0.5f; // radians per second
	const int STARTING_HEALTH = 600;
	const int DAMAGE = 50;
	const float GUN_IMAGE_SCALE = 0.24f;
	const float GUN_FRAME_DELAY = 0.08f;
	const int GUN_FRAME_START = 0;
	const int GUN_FRAME_END = 7;
}

class PhotonCannon : public Tower
{
public:
	PhotonCannon();
	~PhotonCannon();

	void update(float frameTime);

	// Not supported. Don't use.
	void attackTarget(Entity* target);

	void attackTargets(std::list<Enemy*> targets);

	float getRange() { return photonCannonNS::RANGE; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

	void repair() { health = photonCannonNS::STARTING_HEALTH; }

private:
	Entity projectile;
	std::list<Enemy*> targets;
};

