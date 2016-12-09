// Created by Samuel Casteel
#pragma once
#include "EnemyManager.h"

class Wave {
public:
    Wave();
    ~Wave();
	void initialize(EnemyManager* manager);
	void reset();
	void setSpawnTime(float spawnTime);
    bool update(float frameTime);
	void addEnemy(char toAdd);

private:
    EnemyManager* manager;
	std::string toSpawn;
	float spawnTime;
    float timeSinceLastSpawn;
};