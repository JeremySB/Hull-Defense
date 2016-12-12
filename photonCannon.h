// Created by Jeremy Bost

#pragma once
#include "structure.h"
#include "enemy.h"
#include "graphics.h"
#include "particleManager.h"

namespace photonCannonNS {
	const int	PRICE = 600;
	const float RANGE = 300.0f;
	const float TIME_BETWEEN_SHOTS = 1.8f;
	const float ROTATE_SPEED = 0.5f; // radians per second
	const int	STARTING_HEALTH = 600;
	const int	DAMAGE = 60;

	const float GUN_IMAGE_SCALE = 0.24f;
	const float GUN_FRAME_DELAY = 0.12f;
	const int	GUN_FRAME_START = 0;
	const int	GUN_FRAME_END = 7;
	
	const float PROJECTILE_IMAGE_SCALE = 0.07f;
	const float PROJECTILE_FRAME_DELAY = 0.08f;
	const int	PROJECTILE_FRAME_START = 0;
	const int	PROJECTILE_FRAME_END = 3;
	const float PROJECTILE_SPEED = 350.0f;

	const float	PROJECTILE_EXPLOSION_RADIUS = 25.0f;
	const float PROJECTILE_EXPLOSION_IMAGE_SCALE = 0.5f;
	const float PROJECTILE_EXPLOSION_DURATION = 0.6f;
}

class PhotonCannon : public Structure
{
public:
	PhotonCannon();
	~PhotonCannon();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM, ParticleManager* particleManager);

	void draw();

	void update(float frameTime);

	void drawProjectiles();

	// Not supported. Don't use.
	void attackTarget(Entity* target);

	// call each frame. Pass all enemies and it will pick one and target it.
	void attackTargets(std::list<Enemy*> targets);

	float getRange() { return photonCannonNS::RANGE; }

	float getMaxHealth() { return photonCannonNS::STARTING_HEALTH; }

	void setProjectileTexture(TextureManager* tm);
	void setGunTexture(TextureManager* tm);

	void repair() { health = photonCannonNS::STARTING_HEALTH; }

private:
	ParticleManager* particleManager;
	
	Entity projectile;
	Entity gunImage;
	Enemy* target;
	std::list<Enemy*> targets;
	float cooldown;

	int targetX, targetY;
	bool canRotate;
};

