#include "turret.h"

// Created by Jeremy Bost

Turret::Turret()
{
	Structure::Structure();
	type = turret;
	setCollisionRadius(turretNS::RANGE);
	projectileDisplayTimer = turretNS::PROJECTILE_DURATION + turretNS::TIME_BETWEEN_SHOTS;
	target = nullptr;
	firstShot = false;
	setHealth(turretNS::STARTING_HEALTH);
}


Turret::~Turret()
{
}

bool Turret::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionRadius(getWidth() / 2.0);
	return result;
}

void Turret::drawProjectiles()
{
	projectileImage.draw(projectileImage.getColorFilter());
	gunImage.draw(graphicsNS::GRAY);
}

void Turret::draw()
{
	//Structure::draw();
	Entity::draw(graphicsNS::BLUE);
	//gunImage.draw();
}

void Turret::update(float frameTime)
{
	Entity::update(frameTime);
	if (projectileDisplayTimer < turretNS::PROJECTILE_DURATION + turretNS::TIME_BETWEEN_SHOTS && target != nullptr)
	{
		float distance = std::sqrt(std::pow(target->getCenterX() - getCenterX(), 2) + std::pow(target->getCenterY() - getCenterY(), 2));
		if (distance <= turretNS::RANGE) {
			// hit is good
			projectileImage.setWidth(distance);
			projectileImage.setRect();
			projectileImage.setX(getCenterX() + (target->getCenterX() - getCenterX()) / 2 - projectileImage.getWidth() / 2);
			projectileImage.setY(getCenterY() + (target->getCenterY() - getCenterY()) / 2 - projectileImage.getHeight() / 2);
			float radians = std::atan2(target->getCenterY() - getCenterY(), target->getCenterX() - getCenterX());
			projectileImage.setRadians(radians);
			gunImage.setRadians(radians + PI / 2);
			
			projectileImage.setVisible(true);
			projectileImage.setColorFilter(SETCOLOR_ARGB((int)(255 * (1 - min(1, projectileDisplayTimer / turretNS::PROJECTILE_DURATION))), 255, 255, 255));
			projectileDisplayTimer += frameTime;

			// apply damage to target
			if(firstShot)
				target->setHealth(target->getHealth() - turretNS::DAMAGE);
			
			firstShot = false;
			
		}
		else
		{
			projectileImage.setVisible(false);
			gunImage.setRadians(gunImage.getRadians() + frameTime * turretNS::ROTATE_SPEED);
		}
	}
	else {
		projectileImage.setVisible(false);
		gunImage.setRadians(gunImage.getRadians() + frameTime * turretNS::ROTATE_SPEED);
	}
}

void Turret::attackTarget(Entity* target)
{
	if (projectileDisplayTimer >= turretNS::PROJECTILE_DURATION + turretNS::TIME_BETWEEN_SHOTS) {
		projectileDisplayTimer = 0;
		firstShot = true;
	}
	if (this->target != target) {
		this->target = target;
		firstShot = true;
	}
}

void Turret::setProjectileTexture(TextureManager * tm)
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

void Turret::setGunTexture(TextureManager * tm)
{
	gunTexture = tm;
	if (!gunImage.initialize(graphics, 0, 0, 0, gunTexture)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret gun image");
	}
	//gunImage.setX(getX());
	//gunImage.setY(getY() - (gunImage.getHeight() - getHeight())/2);

	gunImage.setX(getCenterX() - gunImage.getWidth() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() / 2);
}