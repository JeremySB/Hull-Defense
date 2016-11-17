#include "wall.h"



Wall::Wall()
{
	setHealth(100);
}


Wall::~Wall()
{
}

void Wall::damage(int weapon){
	setHealth(getHealth()-weapon);
}