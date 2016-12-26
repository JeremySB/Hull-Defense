#pragma once

#include "enemy.h"

class PregnantEnemy: public Enemy {
public:
    PregnantEnemy() {
        speed = 30;
        value = 50;
        health = 250;
        damage = 30;
        targeting = baseTarget;
        colorFilter = SETCOLOR_ARGB(255, 255, 255, 0);
    }
};