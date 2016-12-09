// Created by Samuel Casteel
#include "wave.h"
Wave::~Wave(){
}

Wave::Wave():timeSinceLastSpawn(0),spawnTime(0){}

void Wave::initialize(EnemyManager* manager){
	this->manager = manager;
}

bool Wave::update(float frameTime){
    timeSinceLastSpawn += frameTime;
    if(timeSinceLastSpawn > spawnTime){
		switch(toSpawn[0]){
			case('H'):
				manager->addChild(new HeavyEnemy);
				break;
			case('M'):
				manager->addChild(new MediumEnemy);
				break;
			case('L'):
				manager->addChild(new LightEnemy);
				break;
			default:
				break;
			}
		toSpawn.erase(0,1);
		timeSinceLastSpawn = 0;
    }
    return !toSpawn.empty();
}

void Wave::addEnemy(char toAdd){
	toSpawn += toAdd;
}

void Wave::setSpawnTime(float spawnTime){
	this->spawnTime = spawnTime;
}

void Wave::reset(){
	toSpawn = "";
	timeSinceLastSpawn = 0;
}