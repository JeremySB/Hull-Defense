// Created by Jeremy Bost
//
// A turret is a single grid cell structure that shoots enemies in range, as opposed to a tower which is 3 by 3.

#pragma once
#include "structure.h"
class Turret :
	public Structure
{
public:
	Turret();
	~Turret();
};

