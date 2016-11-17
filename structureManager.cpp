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

	if (!turretBaseTexture.initialize(graphics, TURRET_BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret base texture"));

	if (!turretGunTexture.initialize(graphics, TURRET_GUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret gun texture"));

	if (!turretProjectileTexture.initialize(graphics, TURRET_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret projectile texture"));

	if (!goodSelectionTexture.initialize(graphics, GOOD_SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	if (!goodSelectionImage.initialize(graphics, CELL_WIDTH, CELL_HEIGHT, 0, &goodSelectionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection image")); 

	goodSelectionImage.setVisible(false);


	addTurret(40, 40);
	addTurret(100, 100);
	Turret* t1 = (Turret*)(grid.atPixelCoords(40, 40));
	Turret* t2 = (Turret*)(grid.atPixelCoords(100, 100));
	t2->attackTarget(t1);
	addTurretSelection();
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
	turret->initialize(game, 1, 1, 0, &turretBaseTexture);
	grid.addAtPixelCoords(turret, x, y);
	turret->setProjectileTexture(&turretProjectileTexture);
	turret->setGunTexture(&turretGunTexture);

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
	turretBaseTexture.onLostDevice();
	turretGunTexture.onLostDevice();
	turretProjectileTexture.onLostDevice();
	goodSelectionTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
	turretBaseTexture.onResetDevice();
	turretGunTexture.onResetDevice();
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
