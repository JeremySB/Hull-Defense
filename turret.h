// Created by Jeremy Bost
//
// A turret is a single grid cell structure that shoots enemies in range, as opposed to a tower which is 3 by 3.

#pragma once
#include "structure.h"

namespace turretNS {
	const float RANGE = 50;
	const float PROJECTILE_SPEED = 100;
}

class Turret : public Structure
{
public:
	Turret();
	~Turret();

	bool initialize(Game *gamePtr, int widthInGrid, int heightInGrid, int ncols, TextureManager *textureM);

	void update(float frameTime);

	void attackTarget(Entity* target);

private:
	TextureManager projectile;
	Entity* target;
};

