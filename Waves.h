#pragma once
#include "wave.h"
#include "enemyManager.h"
class Waves {
public:
    Waves(EnemyManager* manager);
    void startWave();
    void update(float frameTime);

//private:
    Wave waves[5];
    int currentWave;
    bool betweenWaves;
    float timeBetweenWaves;
    float timePassed;
    EnemyManager *manager;
};