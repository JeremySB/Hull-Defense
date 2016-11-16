// Created by Jeremy Bost

#include "structureManager.h"



StructureManager::StructureManager()
{
	lastLMBState = false;
}


StructureManager::~StructureManager()
{
}

void StructureManager::initialize(Graphics* graphics, Game* game, Input* input)
{
	this->input = input;
	this->game = game;
	this->graphics = graphics;

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	if (!turretTexture.initialize(graphics, TURRET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));

	if (!turretProjectileTexture.initialize(graphics, TURRET_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret projectile texture"));

	if (!goodSelectionTexture.initialize(graphics, GOOD_SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	if (!goodSelectionImage.initialize(graphics, CELL_WIDTH, CELL_HEIGHT, 0, &goodSelectionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection image")); 

	goodSelectionImage.setVisible(false);

	//addTurretSelection();
}

void StructureManager::draw()
{
	grid.draw();
	goodSelectionImage.draw();
}

void StructureManager::update(float frameTime)
{
	grid.update(frameTime);

	selection();

	if (input->getMouseLButton()) lastLMBState = true;
	else lastLMBState = false;
}

bool StructureManager::addTurret(int x, int y)
{
	if (isOccupied(x, y)) return false;

	Turret* turret = new Turret();
	turret->initialize(game, 1, 1, 0, &turretTexture);
	grid.addAtPixelCoords(turret, x, y);
	turret->setProjectileTexture(&turretProjectileTexture);

	return true;
}

bool StructureManager::addWall(int x, int y)
{
	if (isOccupied(x, y)) return false;

	Wall* wall = new Wall();
	wall->initialize(game, 1, 1, 0, &wallTexture);
	grid.addAtPixelCoords(wall, x, y);

	return true;
}

void StructureManager::addTurretSelection()
{
	mode = turretSelection;
}

void StructureManager::addWallSelection()
{
	mode = wallSelection;
}

bool StructureManager::isOccupied(int x, int y)
{
	if (grid.atPixelCoords(x, y) != nullptr) return true;
	return false;
}

void StructureManager::onLostDevice()
{
	wallTexture.onLostDevice();
	turretTexture.onLostDevice();
	turretProjectileTexture.onLostDevice();
	goodSelectionTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
	turretTexture.onResetDevice();
	turretProjectileTexture.onResetDevice();
	goodSelectionTexture.onResetDevice();
}

void StructureManager::selection()
{
	int x = input->getMouseX();
	int y = input->getMouseY();

	// only trigger on LMB up
	if (mode == wallSelection && !input->getMouseLButton() && lastLMBState) {
		addWall(x, y); // function checks for existing structures
	}
	else if (mode == turretSelection && !input->getMouseLButton() && lastLMBState) {
		addTurret(x, y);
	}

	// add green highlight if good selection
	if ((mode == wallSelection || mode == turretSelection)
		&& !isOccupied(x, y) && x > 0 && y > 0 && x < GAME_WIDTH && y < GAME_HEIGHT) {
		goodSelectionImage.setHeight(CELL_HEIGHT);
		goodSelectionImage.setWidth(CELL_WIDTH);
		goodSelectionImage.setX(grid.pixelXLoc(grid.gridXLoc(x)));
		goodSelectionImage.setY(grid.pixelYLoc(grid.gridYLoc(y)));
		goodSelectionImage.setVisible(true);
	}
	else {
		goodSelectionImage.setVisible(false);
	}

	// exit selection mode if right click
	if (mode != normal && input->getMouseRButton()) {
		mode = normal;
	}
}
