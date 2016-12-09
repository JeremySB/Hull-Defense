// Created by Jeremy Bost

#include "photonCannon.h"



PhotonCannon::PhotonCannon()
{
	Structure::Structure();

	widthInGrid = 3;
	heightInGrid = 3;
	target = nullptr;
	colorFilter = graphicsNS::PURPLE;
	type = photonCannon;
	price = photonCannonNS::PRICE;
	health = photonCannonNS::STARTING_HEALTH;
	colorFilter = graphicsNS::CYAN;
	cooldown = photonCannonNS::TIME_BETWEEN_SHOTS;
}


PhotonCannon::~PhotonCannon()
{
}

bool PhotonCannon::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionRadius(getWidth() / 2.0);
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
	gunImage.setRadians(gunImage.getRadians() + frameTime * photonCannonNS::ROTATE_SPEED);
	gunImage.update(frameTime);

	projectile.update(frameTime);

	if (projectile.getActive())
	{
		
	}
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
	if (cooldown >= photonCannonNS::TIME_BETWEEN_SHOTS) {
		float dist = 2000.0f;
		Enemy* closest = nullptr;
		for (auto enemy = targets.begin(); enemy != targets.end(); enemy++) {
			float newDist = std::sqrt(std::pow((*enemy)->getCenterX() - getCenterX(), 2) + std::pow((*enemy)->getCenterY() - getCenterY(), 2));
			if (getRange() >= newDist) {
				if (newDist < dist) {
					closest = *enemy;
					dist = newDist;
				}
			}
		}
		target = closest;

		if (target != nullptr) {
			projectile.setX(getCenterX() - projectile.getWidth() * projectile.getScale() / 2);
			projectile.setY(getCenterY() - projectile.getHeight() * projectile.getScale() / 2);

			projectile.setActive(true);
			projectile.setVisible(true);
		}
		
		cooldown = 0;
		audio->playCue(LASER);
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
}

void PhotonCannon::setGunTexture(TextureManager * tm)
{
	if (!gunImage.initialize(graphics, 126, 345, 8, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon gun image");
	}
	gunImage.setScale(photonCannonNS::GUN_IMAGE_SCALE);
	gunImage.setX(getCenterX() - gunImage.getWidth() * gunImage.getScale() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() * gunImage.getScale() / 2);
	gunImage.setFrames(photonCannonNS::GUN_FRAME_START, photonCannonNS::GUN_FRAME_END);
	gunImage.setFrameDelay(photonCannonNS::GUN_FRAME_DELAY);
	gunImage.setCurrentFrame(photonCannonNS::GUN_FRAME_END);
	gunImage.setLoop(true);
}
