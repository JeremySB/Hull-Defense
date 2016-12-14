// Created by Jeremy Bost
// Manages particles. Automatically hides particles once their time to live is up.
// Create a new member function if you want to create a particle effect

#include "textureManager.h"
#include "particle.h"
#include "game.h"
#include <time.h>
#include <list>

#pragma once
class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void initialize(Graphics* graphics, Game* game);
	void update(float frameTime);
	void draw();

	// set all particles to inactive
	void reset();

	void addGenericExplosion(VECTOR2 center, float scale, float timeToLive);
	void addPhotonExplosion(int centerX, int centerY, float scale, float timeToLive);
	void addSmoke(VECTOR2 center, VECTOR2 vel, float scale, float timeToLive);

	float getVariance();

	void onLostDevice();
	void onResetDevice();

private:
	TextureManager photonExplosionTM, smokeTM, genericExplosionTM;
	Particle** particles;
	Graphics* graphics;
	std::list<TextureManager*> listTM; // add pointers to all texture managers to this for easy onLostDevice, etc
};

