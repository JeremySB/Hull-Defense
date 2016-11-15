// Created by Jeremy Bost
//
// Manager to control structures and the structure grid

#pragma once

#include "structure.h"
#include "structureGrid.h"
#include "textureManager.h"
#include "wall.h"

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
	bool addWall(int x, int y);

	// opens selection process for placing a wall
	void addWallSelection();

	// checking if there is a structure at a given pixel location
	bool isOccupied(int x, int y);

	void onLostDevice();
	void onResetDevice();

private:
	StructureGrid grid;
	TextureManager wallTexture, goodSelectionTexture;
	Image goodSelectionImage;
	Graphics* graphics;
	Game* game;
	Input* input;
	enum Mode {normal, wallSelection, towerSelection, turretSelection} mode;
	bool lastLMBState;

	// runs every update and controls hovering and structure selection
	void selection();
};

