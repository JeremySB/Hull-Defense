// Created by Jeremy Bost for Hull Defense
// 
// Creates a grid of structures that contains wall and tower entities.
// Allows structure placement in the grid and returns entities at given positions.

#pragma once

#include "entity.h"
#include <vector>

class structureGrid
{
public:
	structureGrid(void);
	~structureGrid(void);

	// Initialize grid with a certain cell width and height. Grid fills screen.
	void initialize(float cellWidth, float cellHeight);

	// add entity at grid location
	void addAtGridCoords(Entity* ent, int x, int y);

	// add entity at pixel location - translates into nearest grid
	void addAtPixelCoords(Entity* ent, int x, int y);

private:
	float cellWidth, cellHeight;
	std::vector< std::vector<Entity*> > entities;
};

