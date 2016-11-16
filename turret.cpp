#include "turret.h"



Turret::Turret()
{
	setCollisionRadius(turretNS::RANGE);
	projectileDisplayTimer = 0;
	target = nullptr;
	targetChanged = false;
}


Turret::~Turret()
{
}

void Turret::draw()
{
	Structure::draw();
	projectileImage.draw(projectileImage.getColorFilter());
}

void Turret::update(float frameTime)
{
	Entity::update(frameTime);
	setDegrees(getDegrees() + 1);
	if (projectileDisplayTimer < turretNS::PROJECTILE_DURATION) {
		projectileImage.setVisible(true);
		projectileImage.setColorFilter(SETCOLOR_ARGB((int)(255 * (1 - projectileDisplayTimer/ turretNS::PROJECTILE_DURATION)), 255, 255, 255));
		projectileDisplayTimer += frameTime;
	}
	else {
		projectileImage.setVisible(false);
	}
}

void Turret::attackTarget(Entity* target)
{
	if (projectileDisplayTimer >= turretNS::PROJECTILE_DURATION) {
		projectileDisplayTimer = 0;
	}
	if (this->target != target) {
		this->target = target;
		targetChanged = false;
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
	projectileImage.setColorFilter(graphicsNS::WHITE);
}
