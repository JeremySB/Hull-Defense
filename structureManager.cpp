#include "structureManager.h"



StructureManager::StructureManager()
{
}


StructureManager::~StructureManager()
{
}

void StructureManager::initialize(Graphics* graphics)
{
	this->graphics = graphics;
	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	addWall(3, 4);
}

void StructureManager::addWall(int x, int y)
{
	Wall wall;
	wall.initialize();
}

void StructureManager::onLostDevice()
{
	wallTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
}
