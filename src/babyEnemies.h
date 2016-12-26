#pragma once
#include "Enemy.h"

class BabyEnemy : public Enemy {
public:
    BabyEnemy() {
        speed = 125;
        value = 5;
        health = 21;
        damage = 20;
        targeting = baseTarget;
        colorFilter = SETCOLOR_ARGB(255, 255, 200, 0);
        setScale(.75);
    }
};