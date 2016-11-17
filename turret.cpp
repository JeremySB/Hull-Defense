#include "turret.h"



Turret::Turret()
{
	setCollisionRadius(turretNS::RANGE);
	projectileDisplayTimer = turretNS::PROJECTILE_DURATION;
	target = nullptr;
	targetChanged = false;
	setHealth(100);
	type = turret;
}


Turret::~Turret()
{
}

void Turret::drawProjectiles()
{
	projectileImage.draw(projectileImage.getColorFilter());
}

void Turret::update(float frameTime)
{
	Entity::update(frameTime);
	if (projectileDisplayTimer < turretNS::PROJECTILE_DURATION + turretNS::TIME_BETWEEN_SHOTS) {
		if (targetChanged && target != nullptr) {
			float distance = std::sqrt(std::pow(target->getCenterX() - getCenterX(), 2) + std::pow(target->getCenterX() - getCenterX(), 2));
			projectileImage.setWidth(distance);
			projectileImage.setRect();
			projectileImage.setX(getCenterX() + (target->getCenterX() - getCenterX())/2 - projectileImage.getWidth()/2);
			projectileImage.setY(getCenterY() + (target->getCenterY() - getCenterY()) / 2 - projectileImage.getHeight() / 2);
			projectileImage.setRadians(std::atan2(target->getCenterY() - getCenterY(), target->getCenterX() - getCenterX()));
			targetChanged = false;
		}
		projectileImage.setVisible(true);
		projectileImage.setColorFilter(SETCOLOR_ARGB((int)(255 * (1 - min(1, projectileDisplayTimer / turretNS::PROJECTILE_DURATION))), 255, 255, 255));
		projectileDisplayTimer += frameTime;
	}
	else {
		projectileImage.setVisible(false);
		projectileDisplayTimer = 0;
	}
}

void Turret::attackTarget(Entity* target)
{
	if (projectileDisplayTimer >= turretNS::PROJECTILE_DURATION + turretNS::TIME_BETWEEN_SHOTS) {
		projectileDisplayTimer = 0;
	}
	if (this->target != target) {
		this->target = target;
		targetChanged = true;
	}
}

void Turret::setProjectileTexture(TextureManager * tm)
{
	projectileTexture = tm;
	if (!projectileImage.initialize(graphics, 100, 0, 0, projectileTexture)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile image");
	}

	projectileImage.setX(getX());
	projectileImage.setY(getY());
	projectileImage.setWidth(0);
	projectileImage.setRect();
	projectileImage.setColorFilter(graphicsNS::WHITE);
}

void Turret::damage(int weapon){
	setHealth(getHealth()-weapon);
}