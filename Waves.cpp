// Created by Samuel Casteel
#include "Waves.h"
Waves::~Waves(){
}
Waves::Waves(EnemyManager* manager):betweenWaves(true),currentWave(0),timeBetweenWaves(10),timePassed(0){
    this->manager = manager;
    for(int j = 0; j < 5; j++){
        waves[j].manager=manager;
    }
}
void Waves::startWave(){
    //this->betweenWaves =  currentWave == 5;
}
void Waves::update(float frameTime){
    timePassed += frameTime;
    if(!betweenWaves && this->timeBetweenWaves <= timePassed && currentWave < 5 && !this->waves[currentWave].update(frameTime)){
        this->currentWave++;
        this->betweenWaves = true;
    }
    if(betweenWaves && manager->getNumChildren() == 0){
        this->betweenWaves = false;
        timePassed = 0;
    }
}