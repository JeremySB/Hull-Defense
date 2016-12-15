// Created by Jeremy Bost

#include "photonCannon.h"



PhotonCannon::PhotonCannon()
{
	widthInGrid = 3;
	heightInGrid = 3;
	target = nullptr;
	colorFilter = graphicsNS::PURPLE;
	type = photonCannon;
	price = photonCannonNS::PRICE;
	health = photonCannonNS::STARTING_HEALTH;
	colorFilter = graphicsNS::WHITE;
	cooldown = photonCannonNS::TIME_BETWEEN_SHOTS;
}


PhotonCannon::~PhotonCannon()
{
}

bool PhotonCannon::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM, ParticleManager* particleManager)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionRadius(getWidth() / 2.0);
	this->particleManager = particleManager;
	return result;
}

void PhotonCannon::draw()
{
	Structure::draw();
	gunImage.draw(graphicsNS::FILTER);
}

void PhotonCannon::update(float frameTime)
{
	Entity::update(frameTime);
	if(cooldown <= photonCannonNS::TIME_BETWEEN_SHOTS) cooldown += frameTime;
	if (canRotate) {
		gunImage.rotate(frameTime, photonCannonNS::ROTATE_SPEED);
	}
	gunImage.update(frameTime);

	if (projectile.getActive())
	{
		projectile.moveTo(frameTime, photonCannonNS::PROJECTILE_SPEED, targetX, targetY);
	}
	projectile.update(frameTime);
}

void PhotonCannon::drawProjectiles()
{
	projectile.draw();
}

void PhotonCannon::attackTarget(Entity * target)
{
	throw(GameError(gameErrorNS::FATAL_ERROR, "Error: PhotonCannon::attackTarget() not supported"));
}

void PhotonCannon::attackTargets(std::list<Enemy*> targets)
{
	this->targets = targets;
	float dist = 9999999.0f; // using dist squared
	Enemy* closest = nullptr;
	bool targetAlive = false;
	for (auto enemy = targets.begin(); enemy != targets.end(); enemy++) {
		float newDist = std::pow((*enemy)->getCenterX() - getCenterX(), 2) + std::pow((*enemy)->getCenterY() - getCenterY(), 2);
		if (std::pow(getRange(), 2) >= newDist) {
			if (newDist < dist) {
				closest = *enemy;
				dist = newDist;
			}
		}
		if (*enemy == target) {
			targetAlive = true;
		}
	}

	if (!targetAlive)
	{
		target = nullptr;
	}
	
	// rotate gun image towards closest
	if (closest != nullptr)
	{
		gunImage.setRadians(gunImage.getRadians() + gunImage.angleToTarget(*closest->getCenter()) + PI / 2);
		canRotate = false;
	}
	else
	{
		canRotate = true;
	}
	

	// fire new photon if cooldown is up and there is no projectile out
	if (closest != nullptr && cooldown >= photonCannonNS::TIME_BETWEEN_SHOTS 
		&& !projectile.getActive())
	{
		target = closest;
		cooldown = 0;
		projectile.setX(getCenterX() - projectile.getWidth() * projectile.getScale() / 2);
		projectile.setY(getCenterY() - projectile.getHeight() * projectile.getScale() / 2);

		projectile.setActive(true);
		projectile.setVisible(true);
		gunImage.setCurrentFrame(photonCannonNS::PROJECTILE_FRAME_START);
		audio->playCue(PHOTON_CUE);
	}

	

	// update target coords if target exists
	if (target != nullptr)
	{
		targetX = target->getCenterX();
		targetY = target->getCenterY();
	}
	else
	{
		projectile.setActive(false);
		projectile.setVisible(false);
	}

	// check for projectile collisions with enemies and explode if one happens
	if (projectile.getActive())
	{
		bool hit = false;

		for (auto enemy = targets.begin(); enemy != targets.end(); enemy++) {
			if ((*enemy)->collidesWith(projectile, VECTOR2()))
			{
				hit = true;
				break;
			}
		}

		// check if should explode
		if (hit || (projectile.getCenterX() == targetX && projectile.getCenterY() == targetY))
		{
			// increase collision radius to explosion range and apply damage to all collisions
			projectile.setCollisionRadius(photonCannonNS::PROJECTILE_EXPLOSION_RADIUS);
			for (auto enemy = targets.begin(); enemy != targets.end(); enemy++) {
				// difference between centers
				distSquared = *projectile.getCenter() - *(*enemy)->getCenter();
				distSquared.x = distSquared.x * distSquared.x;      // difference squared
				distSquared.y = distSquared.y * distSquared.y;

				// Calculate the sum of the radii (adjusted for scale)
				sumRadiiSquared = (projectile.getRadius()) + ((*enemy)->getRadius()*(*enemy)->getScale());
				sumRadiiSquared *= sumRadiiSquared;                 // square it

				// if entities are colliding
				if ((distSquared.x + distSquared.y) < sumRadiiSquared)
				{
					(*enemy)->setHealth((*enemy)->getHealth() - photonCannonNS::DAMAGE);
				}
			}
			// set back
			projectile.setCollisionRadius(projectile.getWidth() * projectile.getScale() / 2);
			projectile.setActive(false);
			projectile.setVisible(false);
			this->target = nullptr;
			particleManager->addPhotonExplosion(projectile.getCenterX(), projectile.getCenterY(), 
				photonCannonNS::PROJECTILE_EXPLOSION_IMAGE_SCALE, photonCannonNS::PROJECTILE_EXPLOSION_DURATION);
		}
	}

}

void PhotonCannon::setProjectileTexture(TextureManager * tm)
{
	if (!projectile.initialize(gamePtr, 525, 525, 4, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile image");
	}

	projectile.setX(getX());
	projectile.setY(getY());
	projectile.setFrames(photonCannonNS::PROJECTILE_FRAME_START, photonCannonNS::PROJECTILE_FRAME_END);
	projectile.setFrameDelay(photonCannonNS::PROJECTILE_FRAME_DELAY);
	projectile.setCurrentFrame(photonCannonNS::PROJECTILE_FRAME_END);
	projectile.setLoop(true);
	projectile.setScale(photonCannonNS::PROJECTILE_IMAGE_SCALE);
	projectile.setColorFilter(graphicsNS::WHITE);
	projectile.setActive(false);
	projectile.setVisible(false);
	projectile.setCollisionRadius(projectile.getWidth() * projectile.getScale() / 2);
}

void PhotonCannon::setGunTexture(TextureManager * tm)
{
	if (!gunImage.initialize(gamePtr, 126, 345, 8, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon gun image");
	}
	gunImage.setScale(photonCannonNS::GUN_IMAGE_SCALE);
	gunImage.setX(getCenterX() - gunImage.getWidth() * gunImage.getScale() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() * gunImage.getScale() / 2);
	gunImage.setFrames(photonCannonNS::GUN_FRAME_START, photonCannonNS::GUN_FRAME_END);
	gunImage.setFrameDelay(photonCannonNS::GUN_FRAME_DELAY);
	gunImage.setCurrentFrame(photonCannonNS::GUN_FRAME_END);
	gunImage.setLoop(false);
}
