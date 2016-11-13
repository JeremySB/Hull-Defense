// Created by Jeremy Bost
//
// Manager to control structures and the structure grid

#pragma once

#include "structure.h"
#include "structureGrid.h"

class StructureManager
{
public:
	StructureManager();
	~StructureManager();

	// update structures
	void update(float frameTime) { grid.update(frameTime); }

private:
	StructureGrid grid;
};

