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
	listTM.push_back(&photonExplosionTM);

	smokeTM.initialize(graphics, SMOKE_PARTICLE);
	listTM.push_back(&smokeTM);
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

void ParticleManager::reset()
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (particles[i]->getActive())
		{
			particles[i]->setActive(false);
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

void ParticleManager::addSmoke(int centerX, int centerY, float scale, float timeToLive)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i]->getActive())
		{
			particles[i]->initialize(graphics, 256, 256, 8, &smokeTM);
			particles[i]->setFrames(0, 15);
			particles[i]->setFrameDelay(timeToLive / 16.0);
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
	for (auto tm = listTM.begin(); tm != listTM.end(); tm++)
	{
		(*tm)->onLostDevice();
	}
}

void ParticleManager::onResetDevice()
{
	for (auto tm = listTM.begin(); tm != listTM.end(); tm++)
	{
		(*tm)->onResetDevice();
	}
}
