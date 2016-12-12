// Created by Jeremy Bost

#include "structure.h"



Structure::Structure()
{
	Entity::Entity();
	widthInGrid = 1;
	heightInGrid = 1;
	setActive(true);
}


Structure::~Structure()
{
}

bool Structure::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	this->widthInGrid = widthInGrid;
	this->heightInGrid = heightInGrid;
	this->gamePtr = gamePtr;
	int width = widthInGrid * CELL_WIDTH;
	int height = heightInGrid * CELL_HEIGHT;
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Structure::damage(float weapon)
{
	setHealth(getHealth() - weapon);
}

void Structure::setHealth(float health)
{
	Entity::setHealth(health);
	healthbar.setCurrentFrame((1 - (health / getMaxHealth())) * 37);
	if (getHealth() <= getMaxHealth() - 1)
	{
		healthbar.setVisible(true);
	}
	else {
		healthbar.setVisible(false);
	}
}

void Structure::setupHealthbar(TextureManager* healthbarTexture){
    healthbar.initialize(graphics, 200, 20, 39, healthbarTexture);
    healthbar.setScale(.15);
	healthbar.setVisible(false);
}

void Structure::drawHealthbar(){
    this->healthbar.draw();
}

void Structure::setX(float newX){
    Entity::setX(newX);
    healthbar.setX(getCenterX() - (healthbar.getWidth() / 2) * healthbar.getScale());
    healthbar.setY(Entity::getCenterY() + 10);
}

void Structure::setY(float newY) {
    Entity::setY(newY);
    healthbar.setX(getCenterX() - (healthbar.getWidth() / 2) * healthbar.getScale());
    healthbar.setY(Entity::getCenterY() + 10);
}