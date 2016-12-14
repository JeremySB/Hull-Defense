// Created by Jeremy Bost
// Manages particles. Automatically hides particles once their time to live is up.
// Create a new member function if you want to create a particle effect

#include "textureManager.h"
#include "particle.h"
#include "game.h"
#include <time.h>

#pragma once
class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void initialize(Graphics* graphics, Game* game);
	void update(float frameTime);
	void draw();

	void addPhotonExplosion(int centerX, int centerY, float scale, float timeToLive);
	void addEnemyDeath(Entity *source);
	void addStructurePlacement(Entity *source);
	float getVariance();

	void onLostDevice();
	void onResetDevice();

private:
	TextureManager photonExplosionTM;
	TextureManager enemyDeathTexture;
	Particle** particles;
	Graphics* graphics;
};

