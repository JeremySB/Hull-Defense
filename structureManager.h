// Created by Jeremy Bost
//
// Manager to control structures and the structure grid

#pragma once

#include "structure.h"
#include "structureGrid.h"
#include "textureManager.h"
#include "wall.h"
#include "turret.h"
#include "tower.h"

class StructureManager
{
public:
	StructureManager();
	~StructureManager();

	void initialize(Graphics* graphics, Game* game, Input* input);

	void draw();
	
	// update structures
	void update(float frameTime);

	// add wall at location in pixels. Returns false if object there
	bool addTurret(int x, int y);
	// add wall at location in pixels. Returns false if object there
	bool addWall(int x, int y);

	// opens selection process for placing a turret
	void addTurretSelection();
	// opens selection process for placing a wall
	void addWallSelection();

	std::list<Structure*> getStructures() { return grid.getStructures(); }

	// checking if there is a structure at a given pixel location
	bool isOccupied(int x, int y);
    StructureGrid* getGrid();
    bool getPlacedThisFrame();
	void onLostDevice();
	void onResetDevice();

private:
	//StructureGrid grid;
	TextureManager wallTexture, turretTexture, turretProjectileTexture, goodSelectionTexture;
	Image goodSelectionImage;
	Graphics* graphics;
	Game* game;
	Input* input;
	enum Mode {normal, wallSelection, towerSelection, turretSelection} mode;
	bool lastLMBState;
    bool placedThisFrame;
    StructureGrid grid;
	// runs every update and controls hovering and structure selection
	void selection();
};

