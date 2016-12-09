// Created by Jeremy Bost

#pragma once
#include "structure.h"

namespace towerNS {
	const int PRICE = 400;
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

class Tower : public Structure
{
public:
	Tower();
	~Tower();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	virtual void drawProjectiles();
	virtual void draw();
	virtual void update(float frameTime);

	// call this repeatedly to keep attacks going
	virtual void attackTarget(Entity* target);

	virtual float getRange() { return towerNS::RANGE; }

	virtual void setProjectileTexture(TextureManager* tm);
	virtual void setGunTexture(TextureManager* tm);

	virtual void repair() { health = towerNS::STARTING_HEALTH; }

protected:
	TextureManager* projectileTexture, *gunTexture;
	Entity* target;
	Image projectileImage, gunImage;

	float projectileDisplayTimer;
	bool firstShot;
};

