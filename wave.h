#pragma once
#include "EnemyManager.h"

class Wave {
public:
    Wave();
    bool update(float frameTime);
//private:
    EnemyManager* manager;
    std::list<Enemy*> toSpawn;
    float spawnTime;
    float timeSinceLastSpawn;
};