// Created by Jeremy Bost for Hull Defense
// 
// Creates a grid of structures that contains wall and tower entities.
// Allows structure placement in the grid and returns entities at given positions.
//
// x is across, y is down

#pragma once

#include "structure.h"
#include <vector>

class StructureGrid
{
public:
	StructureGrid(void);
	~StructureGrid(void);

	// add Structure at grid location
	void addAtGridCoords(Structure* ent, int x, int y);

	// add Structure at pixel location - translates into nearest grid
	void addAtPixelCoords(Structure* ent, int x, int y);

private:
	float cellWidth, cellHeight;
	std::vector< std::vector<Structure*> > structures;

	int gridXLoc(int pixelLoc);
	int gridYLoc(int pixelLoc);

	int pixelXLoc(int gridLoc);
	int pixelYLoc(int gridLoc);
};

