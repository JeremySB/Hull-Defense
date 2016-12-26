#include "base.h"



Base::Base()
{
	type = base;
	health = baseNS::STARTING_HEALTH;
	widthInGrid = 4;
	heightInGrid = 4;
}


Base::~Base()
{
}


bool Base::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionRadius(getWidth() / 2.0);
	return result;
}

void Base::setupHealthbar(TextureManager * healthbarTexture)
{
	Structure::setupHealthbar(healthbarTexture);
	healthbar.setScale(.25);
}
