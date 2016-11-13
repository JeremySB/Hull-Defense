#pragma once
#include "entity.h"

class Structure : public Entity
{
public:
	Structure();
	~Structure();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	int getWidthInGrid() { return widthInGrid; }
	int getHeightInGrid() { return heightInGrid; }

private:
	int widthInGrid, heightInGrid;
};

