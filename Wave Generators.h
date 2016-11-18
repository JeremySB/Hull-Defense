#pragma once
#include "EnemyManager.h"

void WaveBuilder1(EnemyManager* into){
    into->addChild(new Enemy(Light));

}