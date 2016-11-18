// Created by Jeremy Bost
//
// A turret is a single grid cell structure that shoots enemies in range, as opposed to a tower which is 3 by 3.

#pragma once
#include "structure.h"

namespace turretNS {
	const int PRICE = 100;
	const float RANGE = 150.0f;
	const float PROJECTILE_DURATION = 0.12f; // in seconds
	const float TIME_BETWEEN_SHOTS = 0.7f; // in seconds
	const float ROTATE_SPEED = 0.0f; // radians per second
	const int STARTING_HEALTH = 200;
	const int DAMAGE = 5;
}

class Turret : public Structure
{
public:
	Turret();
	~Turret();

	bool initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM);

	void drawProjectiles();
	void draw();
	void update(float frameTime);

	// call this repeatedly to keep attacks going
	void attackTarget(Entity* target);
	
	float getRange() { return turretNS::RANGE; }

	void repair() { health = turretNS::STARTING_HEALTH; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

private:
	TextureManager* projectileTexture, *gunTexture;
	Entity* target;
	Image projectileImage, gunImage;

	float projectileDisplayTimer;
	bool firstShot;
};

