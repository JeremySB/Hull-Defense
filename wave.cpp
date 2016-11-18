// Created by Samuel Casteel
#include "wave.h"
Wave::Wave():timeSinceLastSpawn(0),spawnTime(0){

}
bool Wave::update(float frameTime){
    timeSinceLastSpawn += frameTime;
    if(timeSinceLastSpawn > spawnTime){
        manager->addChild(toSpawn.front());
        toSpawn.pop_front();
        timeSinceLastSpawn = 0;
    }
    return !toSpawn.empty();
}