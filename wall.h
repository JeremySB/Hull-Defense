// Created by Jeremy Bost
//
// Simple structure subclass for walls.

#pragma once
#include "structure.h"
class Wall : public Structure
{
public:
	Wall();
	~Wall();

	bool initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM);

};

