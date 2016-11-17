#include "turret.h"



Turret::Turret()
{
	type = turret;
	setCollisionRadius(turretNS::RANGE);
	projectileDisplayTimer = turretNS::PROJECTILE_DURATION;
	target = nullptr;
	targetChanged = false;
}


Turret::~Turret()
{
}

void Turret::drawProjectiles()
{
	projectileImage.draw(projectileImage.getColorFilter());
	gunImage.draw();
}

void Turret::draw()
{
	Structure::draw();
	//gunImage.draw();
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
			float radians = std::atan2(target->getCenterY() - getCenterY(), target->getCenterX() - getCenterX());
			projectileImage.setRadians(radians);
			gunImage.setRadians(radians + PI/2);
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
	gunImage.setX(getX());
	gunImage.setY(getY() - (gunImage.getHeight() - getHeight())/2);
}