// Created by Jeremy Bost
//
// Base class for various structures that are to be put into the structure grid.

#pragma once
#include "entity.h"
#include "enemy.h"
#include <list>

class Structure : public Entity
{
public:
	Structure();
	~Structure();

	virtual bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	virtual void draw() { Entity::draw(getColorFilter()); }

	virtual void drawProjectiles() {}
    void setX(float newX);
    void setY(float newY);
	void damage(float weapon);

	void setHealth(float health);
    
    virtual void setupHealthbar(TextureManager * healthbarTexture);
    void drawHealthbar();
	// give structure one target to attack. Not all implement this
	virtual void attackTarget(Entity* target) {}

	// give structure multiple targets to attack. Mostly for AOE structures
	virtual void attackTargets(std::list<Enemy*> targets) {}

	// Get structure's range. Default is 0
	virtual float getRange() { return 0.0f; }

	virtual void repair() {}

	int getWidthInGrid() { return widthInGrid; }
	int getHeightInGrid() { return heightInGrid; }
	int getPrice() { return price; }

	virtual float getMaxHealth() = 0;

	StructureTypes getType(){ return type;}


protected:
	StructureTypes type;
	Game* gamePtr;
    Image healthbar;
	int widthInGrid, heightInGrid;
	int price;
};

