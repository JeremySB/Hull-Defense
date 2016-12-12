#pragma once
#include "structure.h"

namespace baseNS {
	const int STARTING_HEALTH = 1000;
}

class Base :
	public Structure
{
public:
	Base();
	~Base();

	void repair() {}

	float getMaxHealth() { return baseNS::STARTING_HEALTH; }

	bool initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM);
};

