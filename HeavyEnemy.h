#pragma once
#include "Enemy.h"
class HeavyEnemy : public Enemy {
public:
    HeavyEnemy(){
        speed = 10;
        value = 100;
        health = 200;
        damage = 20;
        targeting = weakestTarget;
        colorFilter = SETCOLOR_ARGB(255,0,255,0);
    }
};