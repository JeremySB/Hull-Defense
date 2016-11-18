// Created by Jeremy Bost

#include "structureManager.h"



StructureManager::StructureManager()
{
	lastLMBState = false;
    placedThisFrame = false;
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

	// turret textures
	if (!turretBaseTexture.initialize(graphics, TURRET_BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret base texture"));

	if (!turretGunTexture.initialize(graphics, TURRET_GUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret gun texture"));

	if (!turretProjectileTexture.initialize(graphics, TURRET_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret projectile texture"));

	// tower textures
	if (!towerBaseTexture.initialize(graphics, TOWER_BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower base texture"));

	if (!towerGunTexture.initialize(graphics, TOWER_GUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower gun texture"));

	if (!towerProjectileTexture.initialize(graphics, TOWER_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tower projectile texture"));


	if (!goodSelectionTexture.initialize(graphics, GOOD_SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	if (!goodSelectionImage.initialize(graphics, CELL_WIDTH, CELL_HEIGHT, 0, &goodSelectionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection image")); 

	goodSelectionImage.setVisible(false);


	addTurret(100, 100);
	addTurret(100, 200);
	addTower(200, 200);

	Turret* t1 = (Turret*)(grid.atPixelCoords(100, 100));
	Turret* t2 = (Turret*)(grid.atPixelCoords(100, 200));
	Tower* t3 = (Tower*)(grid.atPixelCoords(200, 200));

	addTowerSelection();
}

void StructureManager::draw()
{
	grid.draw();
	goodSelectionImage.draw();
}

void StructureManager::collisions(std::list<Enemy*> entities)
{
	std::list<Structure*> structures = grid.getStructures();
	structures.remove(NULL);
	entities.remove(NULL);
	for (auto structure = structures.begin(); structure != structures.end(); structure++) {
		float dist = 2000.0f;
		Entity* closest = nullptr;
		for (auto entity = entities.begin(); entity != entities.end(); entity++) {
			if (*entity && (*structure)->collidesWith(**entity, VECTOR2())) {
				float newDist = std::sqrt(std::pow((*entity)->getCenterX() - (*structure)->getCenterX(), 2) + std::pow((*entity)->getCenterY() - (*structure)->getCenterY(), 2));
				if (newDist < dist) {
					closest = *entity;
					dist = newDist;
				}
				(*structure)->attackTarget(*entity);
			}
		}
		(*structure)->attackTarget(closest);
	}
}

void StructureManager::update(float frameTime)
{
	grid.update(frameTime);
    placedThisFrame = !input->getMouseLButton() && lastLMBState;
	selection();

	if (input->getMouseLButton()) lastLMBState = true;
	else lastLMBState = false;
}

bool StructureManager::addTower(int x, int y)
{
	if (isOccupiedAtGrid(grid.gridXLoc(x), grid.gridYLoc(y), 3, 3)) return false;

	Tower* tower = new Tower();
	tower->initialize(game, 3, 3, 0, &towerBaseTexture);
	grid.addAtPixelCoords(tower, x, y);
	tower->setProjectileTexture(&towerProjectileTexture);
	tower->setGunTexture(&towerGunTexture);

	return true;
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

void StructureManager::addTowerSelection()
{
	mode = towerSelection;
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
	towerBaseTexture.onLostDevice();
	towerGunTexture.onLostDevice();
	towerProjectileTexture.onLostDevice();
	goodSelectionTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
	turretBaseTexture.onResetDevice();
	turretGunTexture.onResetDevice();
	turretProjectileTexture.onResetDevice();
	towerBaseTexture.onResetDevice();
	towerGunTexture.onResetDevice();
	towerProjectileTexture.onResetDevice();
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
	else if (mode == towerSelection && !input->getMouseLButton() && lastLMBState) {
		addTower(x, y);
	}

	// add green highlight if good selection
	if ((mode == wallSelection || mode == turretSelection)
		&& !isOccupied(x, y) && x > 0 && y > 0 && x < GAME_WIDTH && y < GAME_HEIGHT) {
		goodSelectionImage.setHeight(CELL_HEIGHT);
		goodSelectionImage.setWidth(CELL_WIDTH);
		goodSelectionImage.setRect();
		goodSelectionImage.setX(grid.pixelXLoc(grid.gridXLoc(x)));
		goodSelectionImage.setY(grid.pixelYLoc(grid.gridYLoc(y)));
		goodSelectionImage.setVisible(true);
	}
	else if ((mode == towerSelection)
		&& !isOccupiedAtGrid(grid.gridXLoc(x), grid.gridYLoc(y), 3, 3) && x > 0 && y > 0 && x < GAME_WIDTH - 2*CELL_WIDTH && y < GAME_HEIGHT - 2 * CELL_HEIGHT) {
		goodSelectionImage.setHeight(3 * CELL_HEIGHT);
		goodSelectionImage.setWidth(3 * CELL_WIDTH);
		goodSelectionImage.setRect();
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


bool StructureManager::isOccupiedAtGrid(int x, int y, int widthInCells, int heightInCells)
{
	for (int i = x; i < x + widthInCells; i++)
	{
		for (int j = y; j < y + heightInCells; j++)
		{
			if (grid.atGridCoords(i, j) != nullptr) {
				return true;
			}
		}
	}
	return false;
}

StructureGrid* StructureManager::getGrid(){
    return &grid;
}

bool StructureManager::getPlacedThisFrame(){
    return this->placedThisFrame;
}