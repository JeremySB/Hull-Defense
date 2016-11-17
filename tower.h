#pragma once
#include "structure.h"

namespace towerNS {
	const float RANGE = 50;
	const float PROJECTILE_DURATION = 0.15; // in seconds
	const float TIME_BETWEEN_SHOTS = 0.5; // in seconds
}

class Tower : public Structure
{
public:
	Tower();
	~Tower();

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

