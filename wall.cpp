#include "wall.h"



Wall::Wall()
{
	Structure::Structure();
	type = wall;
}


Wall::~Wall()
{
}

bool Wall::initialize(Game * gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager * textureM)
{
	bool result = Structure::initialize(gamePtr, widthInGrid, heightInGrid, ncols, textureM);
	setCollisionType(entityNS::BOX);
	RECT rect = { -getWidth() / 2, -getHeight() / 2, getWidth() / 2, getHeight() / 2 };
	setEdge(rect);
	return result;
}