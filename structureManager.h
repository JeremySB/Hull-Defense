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

	void initialize(Graphics* graphics);

	// add wall at location in pixels
	void addWall(int x, int y);

	// update structures
	void update(float frameTime) { grid.update(frameTime); }

	void onLostDevice();
	void onResetDevice();

private:
	StructureGrid grid;
	TextureManager wallTexture;
	Graphics* graphics;
};

