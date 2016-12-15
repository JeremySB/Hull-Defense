
// Created by Jeremy Bost

#include "tower.h"

Tower::Tower()
{
	type = tower;
	target = nullptr;
	
	widthInGrid = 3;
	heightInGrid = 3;

	setHealth(towerNS::STARTING_HEALTH);
	price = towerNS::PRICE;
	colorFilter = graphicsNS::RED;
	cooldown = towerNS::TIME_BETWEEN_SHOTS;
}


Tower::~Tower()
{
}

bool Tower::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM, ParticleManager* particleM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	particleManager = particleM;
	setCollisionRadius(getWidth() / 2.0);
	return result;
}

void Tower::drawProjectiles()
{
	if(projectile.getActive())
		projectile.draw();
}

void Tower::draw()
{
	Structure::draw();
	gunImage.draw(graphicsNS::FILTER);
}

void Tower::update(float frameTime)
{
	Entity::update(frameTime);
	if (cooldown <= towerNS::TIME_BETWEEN_SHOTS) cooldown += frameTime;
	if (canRotate) {
		gunImage.rotate(frameTime, towerNS::ROTATE_SPEED);
	}
	gunImage.update(frameTime);

	if (projectile.getActive())
	{
		projectile.moveTo(frameTime, towerNS::PROJECTILE_SPEED, targetX, targetY);
		float temp = projectile.angleToTarget(targetX, targetY);
		projectile.setRadians(projectile.getRadians() + projectile.angleToTarget(targetX, targetY));
	}
	projectile.update(frameTime);
	//Entity::update(frameTime);
	//gunImage.update(frameTime);
	//if (projectileDisplayTimer < towerNS::PROJECTILE_DURATION + towerNS::TIME_BETWEEN_SHOTS && target != nullptr) 
	//{
	//	float distance = std::sqrt(std::pow(target->getCenterX() - getCenterX(), 2) + std::pow(target->getCenterY() - getCenterY(), 2));
	//	if (distance <= towerNS::RANGE) {
	//		// hit is good
	//		projectileImage.setWidth(distance);
	//		projectileImage.setRect();
	//		projectileImage.setX(getCenterX() + (target->getCenterX() - getCenterX()) / 2 - projectileImage.getWidth() / 2);
	//		projectileImage.setY(getCenterY() + (target->getCenterY() - getCenterY()) / 2 - projectileImage.getHeight() / 2);
	//		float radians = std::atan2(target->getCenterY() - getCenterY(), target->getCenterX() - getCenterX());
	//		projectileImage.setRadians(radians);
	//		gunImage.setRadians(radians + PI / 2);
	//		
	//		projectileImage.setVisible(true);
	//		D3DCOLOR color = (projectileImage.getColorFilter() | (0xff << 24)) & SETCOLOR_ARGB((int)(255 * (1 - min(1, projectileDisplayTimer / towerNS::PROJECTILE_DURATION))), 255, 255, 255);
	//		projectileImage.setColorFilter(color);
	//		
	//		if (firstShot) {
	//			target->setHealth(target->getHealth() - towerNS::DAMAGE);
	//			gunImage.setCurrentFrame(0);
	//		}

	//		firstShot = false;
	//		projectileDisplayTimer += frameTime;

	//		
	//	}
	//	else
	//	{
	//		projectileImage.setVisible(false);
	//		gunImage.setRadians(gunImage.getRadians() + frameTime * towerNS::ROTATE_SPEED);
	//	}
	//}
	//else {
	//	projectileImage.setVisible(false);
	//	gunImage.setRadians(gunImage.getRadians() + frameTime * towerNS::ROTATE_SPEED);
	//}
}

void Tower::attackTarget(Entity* target)
{
	throw(GameError(gameErrorNS::FATAL_ERROR, "Error: PhotonCannon::attackTarget() not supported"));
	/*
	if (target && projectileDisplayTimer >= towerNS::PROJECTILE_DURATION + towerNS::TIME_BETWEEN_SHOTS) {
		projectileDisplayTimer = 0;
		firstShot = true;
		audio->playCue(LASER);
	}
	this->target = target;
	*/
}

void Tower::attackTargets(std::list<Enemy*> targets)
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


	// fire if cooldown is up and there is no projectile out
	if (closest != nullptr && cooldown >= towerNS::TIME_BETWEEN_SHOTS
		&& !projectile.getActive())
	{
		target = closest;
		cooldown = 0;
		
		projectile.setX(getCenterX() - projectile.getWidth() * projectile.getScale() / 2);
		projectile.setY(getCenterY() - projectile.getHeight() * projectile.getScale() / 2);

		projectile.setActive(true);
		projectile.setVisible(true);
		gunImage.setCurrentFrame(towerNS::GUN_FRAME_START);
		audio->playCue(LASER_CUE);
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
	
		for (auto enemy = targets.begin(); enemy != targets.end(); enemy++) {
			if ((*enemy)->collidesWith(projectile, VECTOR2()))
			{
				(*enemy)->setHealth((*enemy)->getHealth() - towerNS::DAMAGE);
				projectile.setActive(false);
				projectile.setVisible(false);
				this->target = nullptr;
				particleManager->addLaserSparks(*projectile.getCenter(), VECTOR2(0, 0), 0.8, 0.3);
				break;
			}
		}

	}

}


void Tower::setProjectileTexture(TextureManager * tm) 
{
	if (!projectile.initialize(gamePtr, 0, 0, 0, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing projectile image");
	}

	projectile.setX(getX());
	projectile.setY(getY());
	projectile.setScale(towerNS::PROJECTILE_IMAGE_SCALE);
	projectile.setColorFilter(graphicsNS::WHITE);
	projectile.setCollisionRadius(towerNS::PROJECTILE_COLLISION_RADIUS);
}

void Tower::setGunTexture(TextureManager * tm)
{
	if (!gunImage.initialize(gamePtr, 35, 79, 5, tm)) {
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower gun image");
	}
	gunImage.setX(getCenterX() - gunImage.getWidth() * gunImage.getScale() / 2);
	gunImage.setY(getCenterY() - gunImage.getHeight() * gunImage.getScale() / 2);
	gunImage.setFrames(towerNS::GUN_FRAME_START, towerNS::GUN_FRAME_END);
	gunImage.setFrameDelay(towerNS::GUN_FRAME_DELAY);
	gunImage.setCurrentFrame(towerNS::GUN_FRAME_END);
	gunImage.setLoop(false);
}