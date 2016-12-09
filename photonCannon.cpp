// Created by Jeremy Bost

#include "photonCannon.h"



PhotonCannon::PhotonCannon()
{
	Tower::Tower();

	colorFilter = graphicsNS::PURPLE;
	type = photonCannon;
	projectileDisplayTimer = photonCannonNS::PROJECTILE_DURATION + photonCannonNS::TIME_BETWEEN_SHOTS;
	price = photonCannonNS::PRICE;
	health = photonCannonNS::STARTING_HEALTH;
	colorFilter = graphicsNS::CYAN;
}


PhotonCannon::~PhotonCannon()
{
}

void PhotonCannon::update(float frameTime)
{
	Entity::update(frameTime);
	gunImage.setRadians(gunImage.getRadians() + frameTime * photonCannonNS::ROTATE_SPEED);
	gunImage.update(frameTime);

}

void PhotonCannon::attackTarget(Entity * target)
{
	if (projectileDisplayTimer >= photonCannonNS::PROJECTILE_DURATION + photonCannonNS::TIME_BETWEEN_SHOTS) {
		projectileDisplayTimer = 0;
		firstShot = true;
		audio->playCue(LASER);
	}
	this->target = target;
}

void PhotonCannon::setProjectileTexture(TextureManager * tm)
{
}

void PhotonCannon::setGunTexture(TextureManager * tm)
{
	gunTexture = tm;
	if (!gunImage.initialize(graphics, 126, 345, 8, gunTexture)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower gun image");
	}
	gunImage.setScale(photonCannonNS::GUN_IMAGE_SCALE);
	gunImage.setX(getCenterX() - gunImage.getWidth() * gunImage.getScale() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() * gunImage.getScale() / 2);
	gunImage.setFrames(photonCannonNS::GUN_FRAME_START, photonCannonNS::GUN_FRAME_END);
	gunImage.setFrameDelay(photonCannonNS::GUN_FRAME_DELAY);
	gunImage.setCurrentFrame(photonCannonNS::GUN_FRAME_END);
	gunImage.setLoop(true);
}
