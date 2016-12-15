// Created by Jeremy Bost

#include "structureManager.h"



StructureManager::StructureManager()
{
	lastLMBState = false;
    placedThisFrame = false;
	particleTimer = 0;
}


StructureManager::~StructureManager()
{

}

void StructureManager::initialize(Graphics* graphics, Game* game, Input* input, GameState* gameState, ParticleManager* particleManager)
{
	this->input = input;
	this->game = game;
	this->graphics = graphics;
	this->gameState = gameState;
	this->particleManager = particleManager;

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
	if (!photonCannonBaseTexture.initialize(graphics, PHOTON_CANNON_BASE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon base texture"));
	
	if (!photonCannonGunTexture.initialize(graphics, PHOTON_CANNON_GUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon gun texture"));

	if (!photonCannonProjectileTexture.initialize(graphics, PHOTON_CANNON_PROJECTILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing photon cannon projectile texture"));


	if (!goodSelectionTexture.initialize(graphics, GOOD_SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	if (!goodSelectionImage.initialize(graphics, CELL_WIDTH, CELL_HEIGHT, 0, &goodSelectionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection image")); 
    
	goodSelectionImage.setVisible(false);

    if (!healthbarTexture.initialize(graphics, HEALTHBAR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthbar texture"));
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
		// check if structure takes multiple enemies
		if ((*structure)->getType() == photonCannon || (*structure)->getType() == tower)
		{
			(*structure)->attackTargets(entities);
			continue;
		}

		float dist = 2000.0f;
		Entity* closest = nullptr;
		for (auto entity = entities.begin(); entity != entities.end(); entity++) {
			float newDist = std::sqrt(std::pow((*entity)->getCenterX() - (*structure)->getCenterX(), 2) + std::pow((*entity)->getCenterY() - (*structure)->getCenterY(), 2));
			if ((*structure)->getRange() >= newDist) {
				if (newDist < dist) {
					closest = *entity;
					dist = newDist;
				}
			}
		}
		(*structure)->attackTarget(closest);
	}
}

void StructureManager::update(float frameTime)
{
	particleTimer += frameTime;
	
	placedThisFrame = !input->getMouseLButton() && lastLMBState;
	/*
	if (grid.update(frameTime)) { // grid's update returns true if something was deleted because low health
		placedThisFrame = true;
	}
	*/
	std::list<Structure*> structureList = grid.getStructures();
	for (auto iter = structureList.begin(); iter != structureList.end(); iter++) {
		if (*iter) {
			(*iter)->update(frameTime);
			if ((*iter)->getHealth() <= 0)
			{
				// death effects
				if ((*iter)->getType() == StructureTypes::photonCannon)
				{
					particleManager->addPhotonExplosion((*iter)->getCenterX(), (*iter)->getCenterY(), 0.84, 0.8);
				}
				else if ((*iter)->getType() == StructureTypes::tower || (*iter)->getType() == StructureTypes::base)
				{
					particleManager->addGenericExplosion(*(*iter)->getCenter(), 1.2, 1);
				}
				else if ((*iter)->getType() == StructureTypes::turret)
				{
					particleManager->addGenericExplosion(*(*iter)->getCenter(), 0.7, 1);
				}
				grid.removeAtPixelCoords((*iter)->getX()+1, (*iter)->getY() + 1);
				placedThisFrame = true;
			}
			else if (particleTimer >= PARTICLE_SPAWN_TIME)
			{
				// damage effects
				if ((*iter)->getHealth() <= (*iter)->getMaxHealth() * 2 / 3 
					&& (*iter)->getType() != StructureTypes::wall && (*iter)->getType() != StructureTypes::permWall)
				{
					particleManager->addSmoke(*(*iter)->getCenter(), VECTOR2(10, -20), 0.25, 2);
				}
			}
		}
	}

	if (particleTimer >= PARTICLE_SPAWN_TIME) // if reached 1 second, reset
	{
		particleTimer = 0;
	}
	selection();
	

	if (input->getMouseLButton()) lastLMBState = true;
	else lastLMBState = false;
}

bool StructureManager::addBase(int x, int y, bool gridCoords)
{
	int xGrid = grid.gridXLoc(x);
	int yGrid = grid.gridYLoc(y);

	if (gridCoords)
	{
		xGrid = x;
		yGrid = y;
	}

	if (isOccupiedAtGrid(xGrid, yGrid, 4, 4)) return false;

	Base* base = new Base();
	base->initialize(game, 4, 4, 0, &baseTexture);
    base->setupHealthbar(&healthbarTexture);
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
	tower->setupHealthbar(&healthbarTexture);
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
	cannon->initialize(game, 3, 3, 0, &photonCannonBaseTexture, particleManager);
    cannon->setupHealthbar(&healthbarTexture);
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
    turret->setupHealthbar(&healthbarTexture);
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
    wall->setupHealthbar(&healthbarTexture);
	if (!grid.addAtPixelCoords(wall, x, y)) return false;
	gameState->addCurrency(-wallNS::PRICE);

	return true;
}

bool StructureManager::addPermWall(int x, int y, bool gridCoords)
{
	int xGrid = grid.gridXLoc(x);
	int yGrid = grid.gridYLoc(y);

	if (gridCoords)
	{
		xGrid = x;
		yGrid = y;
	}
	
	if (isOccupiedAtGrid(xGrid, yGrid, 1, 1)) return false;

	PermWall* wall = new PermWall();
	wall->initialize(game, 1, 1, 0, &wallTexture);
	if (!grid.addAtGridCoords(wall, xGrid, yGrid)) return false;

	return true;
}

void StructureManager::sell(int x, int y)
{
	if (!isOccupied(x, y)) return;
	Structure* toSell = grid.atPixelCoords(x, y);
	if (toSell->getType() == StructureTypes::base || toSell->getType() == StructureTypes::permWall) return;
	gameState->addCurrency(toSell->getPrice()*2/3);
	Audio* audio = game->getAudio();
	audio->playCue(ENERGY_CUE);
	grid.removeAtPixelCoords(x, y);
	gameState->setSelectionMode(GameState::normal);
}

void StructureManager::repair(int x, int y)
{
	if (!isOccupied(x, y)) return;
	Structure* toRepair = grid.atPixelCoords(x, y);
	if (toRepair->getType() == StructureTypes::base || toRepair->getType() == StructureTypes::permWall || toRepair->getPrice() / 2 > gameState->getCurrency()) return;
	gameState->addCurrency(- (toRepair->getPrice() / 2));
	Audio* audio = game->getAudio();
	audio->playCue(REPAIR_CUE);
	toRepair->repair();
	gameState->setSelectionMode(GameState::normal);
}

bool StructureManager::canRepair(int x, int y)
{
	if (!isOccupied(x, y)) return false;
	Structure* toRepair = grid.atPixelCoords(x, y);
	if (toRepair->getType() == StructureTypes::base || toRepair->getType() == StructureTypes::permWall || toRepair->getPrice() / 2 > gameState->getCurrency()) return false;
	return true;
}

void StructureManager::loadLevel(int x)
{
	reset();
	switch (x)
	{
		case 1:
			addBase(40, 9);
			addPermWall(43, 15); addPermWall(42, 15); addPermWall(41, 15); addPermWall(43, 6); addPermWall(42, 6); addPermWall(41, 6); addPermWall(38, 15); addPermWall(37, 15); addPermWall(38, 6); addPermWall(37, 6); addPermWall(36, 15); addPermWall(36, 6); addPermWall(36, 9); addPermWall(36, 10); addPermWall(36, 11); addPermWall(36, 12); addPermWall(34, 15); addPermWall(34, 14); addPermWall(34, 13); addPermWall(34, 12); addPermWall(34, 6); addPermWall(34, 7); addPermWall(34, 8); addPermWall(34, 9);
			break;
		case 2:
			addBase(40, 0); 
			addPermWall(28, 9); addPermWall(28, 8); addPermWall(28, 3); addPermWall(28, 2); addPermWall(28, 0); addPermWall(28, 1); addPermWall(8, 23); addPermWall(28, 6); addPermWall(28, 7); addPermWall(7, 23); addPermWall(28, 12); addPermWall(29, 12); addPermWall(30, 12); addPermWall(31, 12); addPermWall(34, 12); addPermWall(35, 12); addPermWall(36, 12); addPermWall(37, 12); addPermWall(40, 12); addPermWall(41, 12); addPermWall(42, 12); addPermWall(43, 12); addPermWall(8, 23); addPermWall(31, 2); addPermWall(31, 3); addPermWall(31, 5); addPermWall(31, 6); addPermWall(31, 4); addPermWall(7, 23); addPermWall(31, 8); addPermWall(31, 9); addPermWall(31, 10); addPermWall(32, 10); addPermWall(33, 10); addPermWall(34, 10); addPermWall(37, 10); addPermWall(38, 10); addPermWall(39, 10); addPermWall(40, 10);
			break;
		case 3:
			addBase(19, 9);
			addPermWall(19, 7); addPermWall(20, 7); addPermWall(21, 7); addPermWall(22, 7); addPermWall(18, 7); addPermWall(23, 7); addPermWall(23, 14); addPermWall(22, 14); addPermWall(21, 14); addPermWall(20, 14); addPermWall(19, 14); addPermWall(18, 14); addPermWall(24, 7); addPermWall(17, 7); addPermWall(24, 14); addPermWall(17, 14); addPermWall(14, 7); addPermWall(14, 8); addPermWall(14, 9); addPermWall(14, 14); addPermWall(14, 13); addPermWall(14, 12); addPermWall(27, 14); addPermWall(27, 13); addPermWall(27, 12); addPermWall(27, 7); addPermWall(27, 8); addPermWall(27, 9);
			break;
	}
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
    healthbarTexture.onLostDevice();
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
    healthbarTexture.onResetDevice();
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

	Audio* audio = game->getAudio();

	// only trigger on LMB up
	if (mode == GameState::wallSelection && !input->getMouseLButton() && lastLMBState) {
		if(addWall(x, y)) // function checks for existing structures
			audio->playCue(PLACEMENT_CUE);
	}
	else if (mode == GameState::turretSelection && !input->getMouseLButton() && lastLMBState) {
		if(addTurret(x, y))
			audio->playCue(PLACEMENT_CUE);
	}
	else if (mode == GameState::towerSelection && !input->getMouseLButton() && lastLMBState) {
		if(addTower(x, y))
			audio->playCue(PLACEMENT_CUE);
	}
	else if (mode == GameState::photonCannonSelection && !input->getMouseLButton() && lastLMBState) {
		if (addPhotonCannon(x, y))
			audio->playCue(PLACEMENT_CUE);
	}
	else if (mode == GameState::sell && !input->getMouseLButton() && lastLMBState) {
		sell(x, y);
	}
	else if (mode == GameState::repair && !input->getMouseLButton() && lastLMBState) {
		repair(x, y);
	}

	// default to green
	goodSelectionImage.setColorFilter(graphicsNS::WHITE);

	switch (mode)
	{
	case GameState::wallSelection:
		if (gameState->getCurrency() < wallNS::PRICE)
		{
			goodSelectionImage.setColorFilter(graphicsNS::RED);
		}
		break;
	case GameState::towerSelection:
		if (gameState->getCurrency() < towerNS::PRICE)
		{
			goodSelectionImage.setColorFilter(graphicsNS::RED);
		}
		break;
	case GameState::photonCannonSelection:
		if (gameState->getCurrency() < photonCannonNS::PRICE)
		{
			goodSelectionImage.setColorFilter(graphicsNS::RED);
		}
		break;
	case GameState::turretSelection:
		if (gameState->getCurrency() < turretNS::PRICE)
		{
			goodSelectionImage.setColorFilter(graphicsNS::RED);
		}
		break;
	case GameState::repair:
		if (!canRepair(x, y))
		{
			goodSelectionImage.setColorFilter(graphicsNS::RED);
		}
		break;
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
