#pragma once

#include "enemy.h"

class MediumEnemy : public Enemy {
public:
    MediumEnemy() {
        speed = 15;
        value = 60;
        health = 100;
        damage = 80;
        targeting = strongestTarget;
        colorFilter = SETCOLOR_ARGB(255, 0, 255, 0);
    }
};