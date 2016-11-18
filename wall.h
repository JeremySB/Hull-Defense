// Created by Jeremy Bost
//
// Simple structure subclass for walls.

#pragma once
#include "structure.h"

namespace wallNS {
	const int PRICE = 20;
	const int STARTING_HEALTH = 50;
}

class Wall : public Structure
{
public:
	Wall();
	~Wall();

	bool initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM);

};

