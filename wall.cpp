#include "wall.h"



Wall::Wall()
{
	setHealth(100);
	type = wall;
}


Wall::~Wall()
{
}

void Wall::damage(int weapon){
	setHealth(getHealth()-weapon);
}