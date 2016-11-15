// Created by Jeremy Bost
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

	// remove structure at a location in pixels
	void removeAtPixelCoords(int x, int y) { removeAtGridCoords(gridXLoc(x), gridXLoc(y)); }

	// remove structure at a location in grid
	void removeAtGridCoords(int x, int y);

	// get structure at a location in pixels
	Structure* atPixelCoords(int x, int y) { return atGridCoords(gridXLoc(x), gridXLoc(y)); }

	// get structure at a location in grid
	Structure* atGridCoords(int x, int y) { return structures[x][y]; }

	void draw();

	// call update on structures in frame
	void update(float frameTime);

	int gridXLoc(int pixelLoc);
	int gridYLoc(int pixelLoc);

	int pixelXLoc(int gridLoc);
	int pixelYLoc(int gridLoc);

private:
	float cellWidth, cellHeight;
	std::vector< std::vector<Structure*> > structures;

	int maxX, maxY;

};

