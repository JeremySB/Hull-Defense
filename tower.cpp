
// Created by Jeremy Bost

#include "tower.h"

Tower::Tower()
{
	Structure::Structure();
	type = tower;
	projectileDisplayTimer = towerNS::PROJECTILE_DURATION + towerNS::TIME_BETWEEN_SHOTS;
	target = nullptr;
	firstShot = false;

	widthInGrid = 3;
	heightInGrid = 3;

	setHealth(towerNS::STARTING_HEALTH);
}


Tower::~Tower()
{
}

bool Tower::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionRadius(getWidth() / 2.0);
	return result;
}

void Tower::drawProjectiles()
{
	projectileImage.draw(projectileImage.getColorFilter());
	gunImage.draw();
}

void Tower::draw()
{
	Structure::draw();
	//gunImage.draw();
}

void Tower::update(float frameTime)
{
	Entity::update(frameTime);
	gunImage.update(frameTime);
	if (projectileDisplayTimer < towerNS::PROJECTILE_DURATION + towerNS::TIME_BETWEEN_SHOTS && target != nullptr) 
	{
		float distance = std::sqrt(std::pow(target->getCenterX() - getCenterX(), 2) + std::pow(target->getCenterY() - getCenterY(), 2));
		if (distance <= towerNS::RANGE) {
			// hit is good
			projectileImage.setWidth(distance);
			projectileImage.setRect();
			projectileImage.setX(getCenterX() + (target->getCenterX() - getCenterX()) / 2 - projectileImage.getWidth() / 2);
			projectileImage.setY(getCenterY() + (target->getCenterY() - getCenterY()) / 2 - projectileImage.getHeight() / 2);
			float radians = std::atan2(target->getCenterY() - getCenterY(), target->getCenterX() - getCenterX());
			projectileImage.setRadians(radians);
			gunImage.setRadians(radians + PI / 2);
			
			projectileImage.setVisible(true);
			projectileImage.setColorFilter(SETCOLOR_ARGB((int)(255 * (1 - min(1, projectileDisplayTimer / towerNS::PROJECTILE_DURATION))), 255, 255, 255));
			
			if (firstShot) {
				target->setHealth(target->getHealth() - towerNS::DAMAGE);
				gunImage.setCurrentFrame(0);
			}

			firstShot = false;
			projectileDisplayTimer += frameTime;

			
		}
		else
		{
			projectileImage.setVisible(false);
			gunImage.setRadians(gunImage.getRadians() + frameTime * towerNS::ROTATE_SPEED);
		}
	}
	else {
		projectileImage.setVisible(false);
		gunImage.setRadians(gunImage.getRadians() + frameTime * towerNS::ROTATE_SPEED);
	}
}

void Tower::attackTarget(Entity* target)
{
	if (projectileDisplayTimer >= towerNS::PROJECTILE_DURATION + towerNS::TIME_BETWEEN_SHOTS) {
		projectileDisplayTimer = 0;
		firstShot = true;
		audio->playCue(LASER);
	}
	if (this->target != target) {
		this->target = target;
		
	}
}

void Tower::setProjectileTexture(TextureManager * tm)
{
	projectileTexture = tm;
	if (!projectileImage.initialize(graphics, 170, 0, 0, projectileTexture)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile image");
	}

	projectileImage.setX(getX());
	projectileImage.setY(getY());
	projectileImage.setWidth(0);
	projectileImage.setRect();
	projectileImage.setColorFilter(graphicsNS::WHITE);
}

void Tower::setGunTexture(TextureManager * tm)
{
	gunTexture = tm;
	if (!gunImage.initialize(graphics, 35, 79, 5, gunTexture)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower gun image");
	}
	gunImage.setX(getCenterX() - gunImage.getWidth() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() / 2);
	gunImage.setFrames(towerNS::GUN_FRAME_START, towerNS::GUN_FRAME_END);
	gunImage.setFrameDelay(towerNS::GUN_FRAME_DELAY);
	gunImage.setCurrentFrame(towerNS::GUN_FRAME_END);
	gunImage.setLoop(false);
}