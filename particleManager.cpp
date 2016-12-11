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

void ParticleManager::initialize(Graphics * graphics, Game * game)
{
	this->graphics = graphics;
	photonExplosionTM.initialize(graphics, PHOTON_CANNON_PROJECTILE_EXPLOSION);
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

void ParticleManager::addPhotonExplosion(int centerX, int centerY, float scale, float timeToLive)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i]->getActive())
		{
			particles[i]->initialize(graphics, 256, 256, 8, &photonExplosionTM);
			particles[i]->setFrames(0, 15);
			particles[i]->setFrameDelay(timeToLive/16.0);
			particles[i]->setCurrentFrame(0);
			particles[i]->setScale(scale);
			particles[i]->setLoop(false);
			particles[i]->setTimeToLive(timeToLive);
			particles[i]->setX(centerX - particles[i]->getWidth() * particles[i]->getScale() / 2);
			particles[i]->setY(centerY - particles[i]->getHeight() * particles[i]->getScale() / 2);
			particles[i]->setActive(true);
			break;
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
