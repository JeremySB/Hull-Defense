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

	void initialize(Graphics* graphics, Game* game);

	void draw() { grid.draw(); }
	
	// update structures
	void update(float frameTime) { grid.update(frameTime); }

	// add wall at location in pixels
	void addWall(int x, int y);

	void onLostDevice();
	void onResetDevice();

private:
	StructureGrid grid;
	TextureManager wallTexture;
	Graphics* graphics;
	Game* game;
};

