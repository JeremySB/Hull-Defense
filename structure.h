// Created by Jeremy Bost
//
// Base class for various structures that are to be put into the structure grid.

#pragma once
#include "entity.h"

class Structure : public Entity
{
public:
	Structure();
	~Structure();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	virtual void draw() { Entity::draw(); }

	int getWidthInGrid() { return widthInGrid; }
	int getHeightInGrid() { return heightInGrid; }

private:
	int widthInGrid, heightInGrid;
};

