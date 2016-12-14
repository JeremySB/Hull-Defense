// Created by Jeremy Bost
//
// Simple structure subclass for walls.

#pragma once
#include "structure.h"

namespace wallNS {
	const int PRICE = 50;
	const int STARTING_HEALTH = 75;
}

class Wall : public Structure
{
public:
	Wall();
	~Wall();

	void repair() { setHealth(wallNS::STARTING_HEALTH); }

	virtual float getMaxHealth() { return wallNS::STARTING_HEALTH; }

	bool initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM);

};

