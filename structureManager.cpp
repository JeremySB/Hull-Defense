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

void StructureManager::initialize(Graphics* graphics, Game* game, Input* input, GameState* gameState)
{
	this->input = input;
	this->game = game;
	this->graphics = graphics;
	this->gameState = gameState;

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	if (!baseTexture.initialize(graphics, BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base texture"));

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

	// photon cannon textures
	if (!photonCannonGunTexture.initialize(graphics, PHOTON_CANNON_GUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon gun texture"));

	if (!photonCannonProjectileTexture.initialize(graphics, TOWER_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon projectile texture"));


	if (!goodSelectionTexture.initialize(graphics, GOOD_SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	if (!goodSelectionImage.initialize(graphics, CELL_WIDTH, CELL_HEIGHT, 0, &goodSelectionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection image")); 

	goodSelectionImage.setVisible(false);

}

void StructureManager::draw()
{
	grid.draw();
	goodSelectionImage.draw(graphicsNS::FILTER);
}

void StructureManager::collisions(std::list<Enemy*> entities)
{
	std::list<Structure*> structures = grid.getStructures();
	structures.remove(NULL);
	//entities.remove(NULL);
	for (auto structure = structures.begin(); structure != structures.end(); structure++) {
		float dist = 2000.0f;
		Entity* closest = nullptr;
		for (auto entity = entities.begin(); entity != entities.end(); entity++) {
			float newDist = std::sqrt(std::pow((*entity)->getCenterX() - (*structure)->getCenterX(), 2) + std::pow((*entity)->getCenterY() - (*structure)->getCenterY(), 2));
			if ((*structure)->getRange() >= newDist) {
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
    placedThisFrame = !input->getMouseLButton() && lastLMBState;
	if (grid.update(frameTime)) { // grid's update returns true if something was deleted because low health
		placedThisFrame = true;
	}
	selection();

	if (input->getMouseLButton()) lastLMBState = true;
	else lastLMBState = false;
}

bool StructureManager::addBase(int x, int y)
{
		
	int xGrid = grid.gridXLoc(x);
	int yGrid = grid.gridYLoc(y);
	if (isOccupiedAtGrid(xGrid, yGrid, 4, 4)) return false;

	Base* base = new Base();
	base->initialize(game, 4, 4, 0, &baseTexture);
	if (!grid.addAtGridCoords(base, xGrid, yGrid)) return false;

	return true;
}

bool StructureManager::addTower(int x, int y)
{
	int xGrid = grid.gridXLoc(x) - 1;
	int yGrid = grid.gridYLoc(y) - 1;
	if (isOccupiedAtGrid(xGrid, yGrid, 3, 3) || gameState->getCurrency() < towerNS::PRICE) return false;

	Tower* tower = new Tower();
	tower->initialize(game, 3, 3, 0, &towerBaseTexture);
	if (!grid.addAtGridCoords(tower, xGrid, yGrid)) return false;
	tower->setProjectileTexture(&towerProjectileTexture);
	tower->setGunTexture(&towerGunTexture);

	gameState->addCurrency(-towerNS::PRICE);

	return true;
}

bool StructureManager::addPhotonCannon(int x, int y)
{
	int xGrid = grid.gridXLoc(x) - 1;
	int yGrid = grid.gridYLoc(y) - 1;
	if (isOccupiedAtGrid(xGrid, yGrid, 3, 3) || gameState->getCurrency() < photonCannonNS::PRICE) return false;

	PhotonCannon* cannon = new PhotonCannon();
	cannon->initialize(game, 3, 3, 0, &towerBaseTexture);
	if (!grid.addAtGridCoords(cannon, xGrid, yGrid)) return false;
	cannon->setProjectileTexture(&photonCannonProjectileTexture);
	cannon->setGunTexture(&photonCannonGunTexture);

	gameState->addCurrency(-photonCannonNS::PRICE);

	return true;
}

bool StructureManager::addTurret(int x, int y)
{
	if (isOccupied(x, y) || gameState->getCurrency() < turretNS::PRICE) return false;

	Turret* turret = new Turret();
	turret->initialize(game, 1, 1, 0, &turretBaseTexture);
	if(!grid.addAtPixelCoords(turret, x, y)) return false;
	turret->setProjectileTexture(&turretProjectileTexture);
	turret->setGunTexture(&turretGunTexture);

	gameState->addCurrency(-turretNS::PRICE);

	return true;
}

bool StructureManager::addWall(int x, int y)
{
	if (isOccupied(x, y) || gameState->getCurrency() < wallNS::PRICE) return false;

	Wall* wall = new Wall();
	wall->initialize(game, 1, 1, 0, &wallTexture);
	if (!grid.addAtPixelCoords(wall, x, y)) return false;
	gameState->addCurrency(-wallNS::PRICE);

	return true;
}

void StructureManager::sell(int x, int y)
{
	if (!isOccupied(x, y)) return;
	Structure* toSell = grid.atPixelCoords(x, y);
	if (toSell->getType() == StructureTypes::base) return;
	gameState->addCurrency(toSell->getPrice()/2);
	grid.removeAtPixelCoords(x, y);
	gameState->setSelectionMode(GameState::normal);
}

void StructureManager::repair(int x, int y)
{
	if (!isOccupied(x, y)) return;
	Structure* toRepair = grid.atPixelCoords(x, y);
	if (toRepair->getType() == StructureTypes::base || toRepair->getPrice() / 2 > gameState->getCurrency()) return;
	gameState->addCurrency(- (toRepair->getPrice() / 2));
	toRepair->repair();
	gameState->setSelectionMode(GameState::normal);
}

void StructureManager::addTowerSelection()
{
	gameState->setSelectionMode(GameState::towerSelection);
}

void StructureManager::addTurretSelection()
{
	gameState->setSelectionMode(GameState::turretSelection);
}

void StructureManager::addWallSelection()
{
	gameState->setSelectionMode(GameState::wallSelection);
}

void StructureManager::sellSelection()
{
	gameState->setSelectionMode(GameState::sell);
}

bool StructureManager::isOccupied(int x, int y)
{
	if (grid.atPixelCoords(x, y) != nullptr) return true;
	return false;
}

void StructureManager::onLostDevice()
{
	wallTexture.onLostDevice();
	baseTexture.onLostDevice();
	turretBaseTexture.onLostDevice();
	turretGunTexture.onLostDevice();
	turretProjectileTexture.onLostDevice();
	towerBaseTexture.onLostDevice();
	towerGunTexture.onLostDevice();
	towerProjectileTexture.onLostDevice();
	photonCannonGunTexture.onLostDevice();
	photonCannonProjectileTexture.onLostDevice();
	goodSelectionTexture.onLostDevice();
}

void StructureManager::onResetDevice()
{
	wallTexture.onResetDevice();
	baseTexture.onResetDevice();
	turretBaseTexture.onResetDevice();
	turretGunTexture.onResetDevice();
	turretProjectileTexture.onResetDevice();
	towerBaseTexture.onResetDevice();
	towerGunTexture.onResetDevice();
	towerProjectileTexture.onResetDevice();
	photonCannonGunTexture.onResetDevice();
	photonCannonProjectileTexture.onResetDevice();
	goodSelectionTexture.onResetDevice();
}

void StructureManager::selection()
{
	int x = input->getMouseX();
	int y = input->getMouseY();

	GameState::SelectionMode mode = gameState->getSelectionMode();

	// check if in menu area
	/*if (y > GAME_HEIGHT - CELL_HEIGHT && !input->getMouseLButton() && lastLMBState) {
		mode = GameState::normal;
	}*/

	// only trigger on LMB up
	if (mode == GameState::wallSelection && !input->getMouseLButton() && lastLMBState) {
		addWall(x, y); // function checks for existing structures
	}
	else if (mode == GameState::turretSelection && !input->getMouseLButton() && lastLMBState) {
		addTurret(x, y);
	}
	else if (mode == GameState::towerSelection && !input->getMouseLButton() && lastLMBState) {
		addTower(x, y);
	}
	else if (mode == GameState::photonCannonSelection && !input->getMouseLButton() && lastLMBState) {
		addPhotonCannon(x, y);
	}
	else if (mode == GameState::sell && !input->getMouseLButton() && lastLMBState) {
		sell(x, y);
	}
	else if (mode == GameState::repair && !input->getMouseLButton() && lastLMBState) {
		repair(x, y);
	}

	// add green highlight if good selection
	if ((mode == GameState::wallSelection || mode == GameState::turretSelection)
			&& !isOccupied(x, y) && x > 0 && y > 0 && x < GAME_WIDTH && y < GAME_HEIGHT - CELL_HEIGHT) {
		goodSelectionImage.setHeight(CELL_HEIGHT);
		goodSelectionImage.setWidth(CELL_WIDTH);
		goodSelectionImage.setRect();
		goodSelectionImage.setX(grid.pixelXLoc(grid.gridXLoc(x)));
		goodSelectionImage.setY(grid.pixelYLoc(grid.gridYLoc(y)));
		goodSelectionImage.setVisible(true);
	}
	else if ((mode == GameState::towerSelection || mode == GameState::photonCannonSelection)
			&& !isOccupiedAtGrid(grid.gridXLoc(x) - 1, grid.gridYLoc(y) - 1, 3, 3) && x > CELL_HEIGHT && y > CELL_HEIGHT && x < GAME_WIDTH - 1 * CELL_WIDTH && y < GAME_HEIGHT - 2 * CELL_HEIGHT) {
		goodSelectionImage.setHeight(3 * CELL_HEIGHT);
		goodSelectionImage.setWidth(3 * CELL_WIDTH);
		goodSelectionImage.setRect();
		goodSelectionImage.setX(grid.pixelXLoc(grid.gridXLoc(x) - 1));
		goodSelectionImage.setY(grid.pixelYLoc(grid.gridYLoc(y) - 1));
		goodSelectionImage.setVisible(true);
	}
	else if ((mode == GameState::sell || mode == GameState::repair) && isOccupied(x, y)) {
		Structure* highlighted = grid.atPixelCoords(x, y);
		if (highlighted->getType() != StructureTypes::base) {
			goodSelectionImage.setHeight(CELL_HEIGHT * highlighted->getHeightInGrid());
			goodSelectionImage.setWidth(CELL_WIDTH * highlighted->getWidthInGrid());
			goodSelectionImage.setRect();
			goodSelectionImage.setX(highlighted->getX());
			goodSelectionImage.setY(highlighted->getY());
			goodSelectionImage.setVisible(true);
		}
		
	}
	else {
		goodSelectionImage.setVisible(false);
	}

	// exit selection mode if right click
	if (mode != GameState::normal && input->getMouseRButton()) {
		mode = GameState::normal;
	}

	gameState->setSelectionMode(mode);
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

int StructureManager::getBaseHealth()
{
	std::list<Structure*> structureList = grid.getStructures();
	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if ((*iter)->getType() == StructureTypes::base) {
			return (*iter)->getHealth();
		}
	}
	return 0;
}

void StructureManager::setBaseHealth(float health)
{
	std::list<Structure*> structureList = grid.getStructures();
	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if ((*iter)->getType() == StructureTypes::base) {
			(*iter)->setHealth(health);
			return;
		}
	}
}

void StructureManager::reset()
{
	grid = StructureGrid();
}
