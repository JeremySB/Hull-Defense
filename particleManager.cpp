#include "particleManager.h"



ParticleManager::ParticleManager()
{
	particles = new Particle*[MAX_PARTICLES];
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		particles[i] = new Particle();
	}
}


ParticleManager::~ParticleManager()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		safeDelete(particles[i]);
	}
	delete[] particles;
}

void ParticleManager::update(float frameTime)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i]->getActive())
		{
			particles[i]->update(frameTime);
		}
	}
}

void ParticleManager::draw()
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i]->getActive())
		{
			particles[i]->draw();
		}
	}
}

float ParticleManager::getVariance()
{
	float foo = (rand());
	foo = ((int)foo % 100) / 100.0f;
	foo += 0.5f;
	return foo;
}

void ParticleManager::onLostDevice()
{
	photonExplosionTM.onLostDevice();
}

void ParticleManager::onResetDevice()
{
	photonExplosionTM.onResetDevice();
}
