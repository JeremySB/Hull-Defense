#include "Waves.h"
Waves::Waves(EnemyManager* manager):betweenWaves(true),currentWave(0),timeBetweenWaves(3),timePassed(0){
    for(int j = 0; j < 5; j++){
        waves[j].manager=manager;
    }
}
void Waves::startWave(){
    //this->betweenWaves =  currentWave == 5;
}
void Waves::update(float frameTime){
    timePassed += frameTime;
    if(this->timeBetweenWaves <= timePassed && currentWave < 5 && !this->waves[currentWave].update(frameTime)){
        this->currentWave++;
        this->betweenWaves = true;
        timePassed = 0;
    }
}