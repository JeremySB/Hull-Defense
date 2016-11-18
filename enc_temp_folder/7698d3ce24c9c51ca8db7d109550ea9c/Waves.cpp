#include "Waves.h"
Waves::Waves(EnemyManager* manager):betweenWaves(true),currentWave(0){
    for(int j = 0; j < 5; j++){
        waves[j].manager=manager;
        waves[j].spawnTime = 1.5;
        for(int i = 0; i < MAX_ENEMIES; i++){
            switch(rand()%3){
            case(0):
                waves[j].toSpawn.push_back(new LightEnemy());
                break;
            case(1):
                waves[j].toSpawn.push_back(new HeavyEnemy());
                break;
            case(2):
                waves[j].toSpawn.push_back(new MediumEnemy());
                break;
            }
        }
    }
}
void Waves::startWave(){
    this->betweenWaves = ! currentWave < 5;
}
void Waves::update(float frameTime){
    if(this->betweenWaves)
        return;
    if(currentWave < 5 && !this->waves[currentWave].update(frameTime)){
        this->currentWave++;
        this->betweenWaves = true;
    }
}