// Created by Jeremy Bost

#pragma once
#include "structure.h"

namespace towerNS {
	const float RANGE = 300.0f;
	const float PROJECTILE_DURATION = 0.12f; // in seconds
	const float TIME_BETWEEN_SHOTS = 0.3f; // in seconds
	const float ROTATE_SPEED = 0.5f; // radians per second
}

class Tower : public Structure
{
public:
	Tower();
	~Tower();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	void drawProjectiles();
	void draw();
	void update(float frameTime);

	// call this repeatedly to keep attacks going
	void attackTarget(Entity* target);

	float getRange() { return towerNS::RANGE; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

private:
	TextureManager* projectileTexture, *gunTexture;
	Entity* target;
	Image projectileImage, gunImage;

	float projectileDisplayTimer;
	bool targetChanged;
};

