// Created by Jeremy Bost

#include "structure.h"



Structure::Structure()
{
	Entity::Entity();
	widthInGrid = 1;
	heightInGrid = 1;
}


Structure::~Structure()
{
}

bool Structure::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	this->widthInGrid = widthInGrid;
	this->heightInGrid = heightInGrid;
	int width = widthInGrid * CELL_WIDTH;
	int height = heightInGrid * CELL_HEIGHT;
	return Entity::initialize(gamePtr, width, height, ncols, textureM);
}

void Structure::damage(int weapon)
{
	setHealth(getHealth() - weapon);
}
