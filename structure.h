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

	virtual bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	virtual void draw() { Entity::draw(); }

	virtual void drawProjectiles() {}

	void damage(int weapon);

	virtual void attackTarget(Entity* target) {}

	// Get structure's range. Default is 0
	virtual float getRange() { return 0.0f; }

	int getWidthInGrid() { return widthInGrid; }
	int getHeightInGrid() { return heightInGrid; }
	int getPrice() { return price; }
	StructureTypes getType(){ return type;}
	
protected:
	StructureTypes type;
	int widthInGrid, heightInGrid;
	int price;
};

