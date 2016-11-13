#include "structureManager.h"



StructureManager::StructureManager()
{
}


StructureManager::~StructureManager()
{
}

void StructureManager::initialize(Graphics* graphics, Game* game)
{
	this->game = game;
	this->graphics = graphics;
	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	addWall(40, 50);
}

void StructureManager::addWall(int x, int y)
{
	Wall* wall = new Wall();
	wall->initialize(game, 1, 1, 0, &wallTexture);
	grid.addAtPixelCoords(wall, x, y);
}

void StructureManager::onLostDevice()
{
	wallTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
}
