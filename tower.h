// Created by Jeremy Bost

#pragma once
#include "structure.h"
#include "particleManager.h"

namespace towerNS {
	const int PRICE = 400;
	const float RANGE = 300.0f;

	const float PROJECTILE_DURATION = 0.12f; // in seconds
	const float PROJECTILE_SPEED = 700.0f;
	const float PROJECTILE_IMAGE_SCALE = 0.7f;
	const float PROJECTILE_COLLISION_RADIUS = 15;

	const float TIME_BETWEEN_SHOTS = 1.4f;//0.3f; // in seconds
	const float ROTATE_SPEED = 0.5f; // radians per second
	const int STARTING_HEALTH = 600;
	const int DAMAGE = 40;
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

	void drawProjectiles();
	void draw();
	void update(float frameTime);

	// call this repeatedly to keep attacks going
	void attackTarget(Entity* target);

	// call each frame. Pass all enemies and it will pick one and target it.
	void attackTargets(std::list<Enemy*> targets);

	float getRange() { return towerNS::RANGE; }

	float getMaxHealth() { return towerNS::STARTING_HEALTH; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

	void repair() { setHealth(towerNS::STARTING_HEALTH); }

private:
	ParticleManager* particleManager;

	Entity projectile;
	Entity gunImage;
	Enemy* target;
	std::list<Enemy*> targets;
	float cooldown;

	int targetX, targetY;
	bool canRotate;
	/*
	TextureManager* projectileTexture, *gunTexture;
	Entity* target;
	Image projectileImage, gunImage;

	float projectileDisplayTimer;
	bool firstShot;
	*/
};

