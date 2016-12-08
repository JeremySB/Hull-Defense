// Created by Jeremy Bost

#include "photonCannon.h"



PhotonCannon::PhotonCannon()
{
	Tower::Tower();

	colorFilter = graphicsNS::PURPLE;
	type = photonCannon;
}


PhotonCannon::~PhotonCannon()
{
}

void PhotonCannon::attackTarget(Entity * target)
{
}

void PhotonCannon::setProjectileTexture(TextureManager * tm)
{
}

void PhotonCannon::setGunTexture(TextureManager * tm)
{
}
