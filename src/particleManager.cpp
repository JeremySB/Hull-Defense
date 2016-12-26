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
	// Note: add all texture managers to the listTM list, and they'll auto resetOnLost and all that
	this->graphics = graphics;
	
	if (!photonExplosionTM.initialize(graphics, PHOTON_CANNON_PROJECTILE_EXPLOSION))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle"));
	listTM.push_back(&photonExplosionTM);

	if (!smokeTM.initialize(graphics, SMOKE_PARTICLE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle"));
	listTM.push_back(&smokeTM);

	if (!genericExplosionTM.initialize(graphics, GENERIC_EXPLOSION))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle"));
	listTM.push_back(&genericExplosionTM);
	
	if (!enemyBloodTM.initialize(graphics, ENEMY_BLOOD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle"));
	listTM.push_back(&enemyBloodTM);

	if (!laserSparksTM.initialize(graphics, SPARKS_PARTICLE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing particle"));
	listTM.push_back(&laserSparksTM);

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
			particles[i]->draw(graphicsNS::FILTER);

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

void ParticleManager::addGenericExplosion(VECTOR2 center, float scale, float timeToLive)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i]->getActive())
		{
			float offset = 30;
			particles[i]->initialize(graphics, 128, 128, 8, &genericExplosionTM);
			particles[i]->setFrames(0, 63);
			particles[i]->setFrameDelay(timeToLive / 64.0);
			particles[i]->setColorFilter(D3DCOLOR_ARGB(255, 255, 255, 255));
			particles[i]->setCurrentFrame(0);
			particles[i]->setScale(scale);
			particles[i]->setVelocity(VECTOR2(0, 0));
			particles[i]->setLoop(false);
			particles[i]->setTimeToLive(timeToLive);
			particles[i]->setX(center.x - (particles[i]->getWidth()) * particles[i]->getScale() / 2);
			particles[i]->setY(center.y - (particles[i]->getHeight() + offset) * particles[i]->getScale() / 2);
			particles[i]->setActive(true);
			break;
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
			particles[i]->setColorFilter(graphicsNS::WHITE);
			particles[i]->setCurrentFrame(0);
			particles[i]->setScale(scale);
			particles[i]->setVelocity(VECTOR2(0,0));
			particles[i]->setLoop(false);
			particles[i]->setTimeToLive(timeToLive);
			particles[i]->setX(centerX - particles[i]->getWidth() * particles[i]->getScale() / 2);
			particles[i]->setY(centerY - particles[i]->getHeight() * particles[i]->getScale() / 2);
			particles[i]->setActive(true);
			break;
		}
	}
}

void ParticleManager::addEnemyDeath(Entity *source){
	int i;
	for (i = 0; i < MAX_PARTICLES && particles[i]->getActive(); i++);
	if(particles[i]->getActive())
		return;
	particles[i]->initialize(graphics, 128, 128, 4, &enemyBloodTM);
	particles[i]->setFrames(0,15);
	particles[i]->setCurrentFrame(0);
	particles[i]->setScale(.25);
	particles[i]->setLoop(false);
	particles[i]->setTimeToLive(.6 * (rand()%21)/20.0);
    particles[i]->setFrameDelay(particles[i]->getTimeToLive() / 15);
	particles[i]->setX(source->getCenterX() - particles[i]->getWidth() * particles[i]->getScale() / 2);
	particles[i]->setY(source->getCenterY() - particles[i]->getHeight() * particles[i]->getScale() / 2);
	particles[i]->setRadians((rand()%11) / 10);
	particles[i]->setVelocity(VECTOR2(30 * (rand()%101) / 100.0,30 * (rand()%101) / 100.0));
	particles[i]->setActive(true);
}

void ParticleManager::addSmoke(VECTOR2 center, VECTOR2 vel, float scale, float timeToLive, int alpha)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i]->getActive())
		{
			vel = VECTOR2(vel.x + 5*getVariance(), vel.y + 5 * getVariance());
			particles[i]->initialize(graphics, 256, 256, 6, &smokeTM);
			particles[i]->setFrames(0, 29);
			particles[i]->setFrameDelay(timeToLive / 30.0);
			particles[i]->setColorFilter(D3DCOLOR_ARGB(alpha, 255, 255, 255));
			particles[i]->setCurrentFrame(0);
			particles[i]->setScale(scale);
			particles[i]->setVelocity(vel);
			particles[i]->setLoop(false);
			particles[i]->setTimeToLive(timeToLive);
			particles[i]->setX(center.x - particles[i]->getWidth() * particles[i]->getScale() / 2);
			particles[i]->setY(center.y - particles[i]->getHeight() * particles[i]->getScale() / 2);
			particles[i]->setActive(true);
			break;
		}
	}
}

void ParticleManager::addLaserSparks(VECTOR2 center, VECTOR2 vel, float scale, float timeToLive)
{
	for (int i = 0; i < MAX_PARTICLES; i++) {
		if (!particles[i]->getActive())
		{
			vel = VECTOR2(vel.x + 3 * getVariance(), vel.y + 3 * getVariance());
			particles[i]->initialize(graphics, 64, 64, 4, &laserSparksTM);
			particles[i]->setFrames(0, 3);
			particles[i]->setFrameDelay(timeToLive / 4.0);
			particles[i]->setColorFilter(D3DCOLOR_ARGB(255, 255, 255, 255));
			particles[i]->setCurrentFrame(0);
			particles[i]->setScale(scale);
			particles[i]->setVelocity(vel);
			particles[i]->setLoop(false);
			particles[i]->setTimeToLive(timeToLive);
            particles[i]->setRadians(rand());
			particles[i]->setX(center.x - particles[i]->getWidth() * particles[i]->getScale() / 2);
			particles[i]->setY(center.y - particles[i]->getHeight() * particles[i]->getScale() / 2);
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
