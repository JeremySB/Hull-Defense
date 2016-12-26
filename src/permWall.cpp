#include "permWall.h"

// Created by Jeremy Bost

PermWall::PermWall()
{
	setColorFilter(D3DCOLOR_ARGB(255, 64, 64, 64));
	health = 99999.0f;
	type = permWall;
}


PermWall::~PermWall()
{
}
