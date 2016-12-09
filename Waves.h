// Created by Samuel Casteel
#pragma once
#include "wave.h"
#include "enemyManager.h"
class Waves {
public:
    Waves();//EnemyManager* manager);
    ~Waves();
	void initialize(EnemyManager* manager);
	void loadWaves(std::string filename);
    void update(float frameTime);
	bool complete();

private:
    Wave waves[5];
    int currentWave;
    bool betweenWaves;
    float timeBetweenWaves;
    float timePassed;
    EnemyManager *manager;
};