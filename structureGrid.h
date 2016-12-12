// Created by Jeremy Bost
// 
// Creates a grid of structures that contains wall and tower entities.
// Allows structure placement in the grid and returns entities at given positions.
//
// x is across, y is down

#pragma once

#include "structure.h"
#include <vector>
#include <list>
#include <set>
#include <utility>

class StructureGrid
{
public:
	StructureGrid(void);
	~StructureGrid(void);

	// add Structure at grid location
	bool addAtGridCoords(Structure* ent, int x, int y);

	// add Structure at pixel location - translates into nearest grid
	bool addAtPixelCoords(Structure* ent, int x, int y);

	// remove structure at a location in pixels
	void removeAtPixelCoords(int x, int y) { removeAtGridCoords(gridXLoc(x), gridXLoc(y)); }

	// remove structure at a location in grid
	void removeAtGridCoords(int x, int y);

	// get structure at a location in pixels
	Structure* atPixelCoords(int x, int y) { return atGridCoords(gridXLoc(x), gridXLoc(y)); }

	// get structure at a location in grid
	Structure* atGridCoords(int x, int y);

	void draw();

	// call update on structures in frame
	bool update(float frameTime);

	std::list<Structure*> getStructures();

	int gridXLoc(int pixelLoc);
	int gridYLoc(int pixelLoc);

	int pixelXLoc(int gridLoc);
	int pixelYLoc(int gridLoc);

private:
	float cellWidth, cellHeight;
	std::vector< std::vector<Structure*> > structures;
	std::list<Structure*> structureList; // used for draw(), update(), etc. Points to things also in the structures vector

	int maxX, maxY;
	std::list<std::pair<int, int>> temp;
};

