// Created by Jeremy Bost
//
// Manager to control structures and the structure grid

#pragma once

#include "structure.h"
#include "structureGrid.h"
#include "textureManager.h"
#include "wall.h"
#include "permWall.h"
#include "turret.h"
#include "tower.h"
#include "photonCannon.h"
#include "Enemy.h"
#include "base.h"
#include "gameState.h"
#include "particleManager.h"
#include <list>

class StructureManager
{
public:
	StructureManager();
	~StructureManager();

	void initialize(Graphics* graphics, Game* game, Input* input, GameState* gameState, ParticleManager* particleManager);

	void draw();

	// input a list of entities to check if they are within any structure's range
	void collisions(std::list<Enemy*> entities);
	
	// update structures
	void update(float frameTime);


	bool addBase(int x, int y, bool gridCoords = true);
	// add tower at location in pixels. Returns false if object there
	bool addTower(int x, int y);
	// add photon cannon at location in pixels. Returns false if object there
	bool addPhotonCannon(int x, int y);
	// add turret at location in pixels. Returns false if object there
	bool addTurret(int x, int y);
	// add wall at location in pixels. Returns false if object there
	bool addWall(int x, int y);


	bool addPermWall(int x, int y, bool gridCoords = true);

	void sell(int x, int y);
	void repair(int x, int y);

	// resets and loads structures for levels 1 to 3
	void loadLevel(int x); 

	// opens selection process for placing a turret
	void addTowerSelection();
	// opens selection process for placing a turret
	void addTurretSelection();
	// opens selection process for placing a wall
	void addWallSelection();

	void sellSelection();

	void removeSelection() { gameState->setSelectionMode(GameState::normal); };

	std::list<Structure*> getStructures() { return grid.getStructures(); }

	// checking if there is a structure at a given pixel location
	bool isOccupied(int x, int y);

	// check if free at grid coords and number of cells
	bool isOccupiedAtGrid(int x, int y, int widthInCells, int heightInCells);

    StructureGrid* getGrid();

    bool getPlacedThisFrame();
	
	int getBaseHealth();

	void setBaseHealth(float health);

	void reset();

	void onLostDevice();
	void onResetDevice();

private:
	TextureManager wallTexture, baseTexture, goodSelectionTexture;
	TextureManager turretProjectileTexture, turretBaseTexture, turretGunTexture;
	TextureManager towerProjectileTexture, towerGunTexture, towerBaseTexture;
	TextureManager photonCannonProjectileTexture, photonCannonGunTexture, photonCannonBaseTexture;
	ParticleManager* particleManager;
	Image goodSelectionImage;
	Graphics* graphics;
	Game* game;
	Input* input;
	GameState* gameState;
	bool lastLMBState;
    bool placedThisFrame;
    StructureGrid grid;
	// runs every update and controls hovering and structure selection
	void selection();
};

