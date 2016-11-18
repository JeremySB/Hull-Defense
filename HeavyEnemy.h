#pragma once
#include "Enemy.h"
class HeavyEnemy : public Enemy {
public:
    HeavyEnemy(){
        speed = 50;
        value = 100;
        health = 2000000000;
        damage = 2000000000;
        targeting = weakestTarget;
        colorFilter = SETCOLOR_ARGB(255,0,125,0);
    }
};