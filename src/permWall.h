#pragma once

// Created by Jeremy Bost
//
// Walls that don't die

#include "wall.h"
class PermWall :
	public Wall
{
public:
	PermWall();
	~PermWall();

	float getMaxHealth() { return 99999.0f; }

	void setHealth() {}

	void damage(int weapon) {};

};

