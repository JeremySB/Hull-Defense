// Created by Jeremy Bost
//
// A turret is a single grid cell structure that shoots enemies in range, as opposed to a tower which is 3 by 3.

#pragma once
#include "structure.h"

namespace turretNS {
	const float RANGE = 50;
	const float PROJECTILE_DURATION = 0.15; // in seconds
	const float TIME_BETWEEN_SHOTS = 0.5; // in seconds
}

class Turret : public Structure
{
public:
	Turret();
	~Turret();

	void drawProjectiles();
	void draw();
	void update(float frameTime);

	void attackTarget(Entity* target);

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

private:
	TextureManager* projectileTexture, *gunTexture;
	Entity* target;
	Image projectileImage, gunImage;

	float projectileDisplayTimer;
	bool targetChanged;
};

