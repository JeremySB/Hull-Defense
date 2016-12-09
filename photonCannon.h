// Created by Jeremy Bost

#pragma once
#include "structure.h"
#include "enemy.h"
#include "graphics.h"

namespace photonCannonNS {
	const int PRICE = 500;
	const float RANGE = 300.0f;
	const float TIME_BETWEEN_SHOTS = 1;//0.3f; // in seconds
	const float ROTATE_SPEED = 0.5f; // radians per second
	const int STARTING_HEALTH = 600;
	const int DAMAGE = 50;

	const float GUN_IMAGE_SCALE = 0.24f;
	const float GUN_FRAME_DELAY = 0.08f;
	const int	GUN_FRAME_START = 0;
	const int	GUN_FRAME_END = 7;
	
	const float PROJECTILE_IMAGE_SCALE = 0.07f;
	const float PROJECTILE_FRAME_DELAY = 0.08f;
	const int	PROJECTILE_FRAME_START = 0;
	const int	PROJECTILE_FRAME_END = 3;
	const float PROJECTILE_SPEED = 20.0f;
}

class PhotonCannon : public Structure
{
public:
	PhotonCannon();
	~PhotonCannon();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	void draw();

	void update(float frameTime);

	void drawProjectiles();

	// Not supported. Don't use.
	void attackTarget(Entity* target);

	void attackTargets(std::list<Enemy*> targets);

	float getRange() { return photonCannonNS::RANGE; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

	void repair() { health = photonCannonNS::STARTING_HEALTH; }

private:
	Entity projectile;
	Image gunImage;
	Enemy* target;
	std::list<Enemy*> targets;
	float cooldown;
};

