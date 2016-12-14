// Created by Samuel Casteel
#pragma once

#include "enemy.h"

class MediumEnemy : public Enemy {
public:
    MediumEnemy() {
        speed = 75;
        value = 45;
        health = 150;
        damage = 50;
        targeting = strongestTarget;
        colorFilter = SETCOLOR_ARGB(255, 0, 125, 0);
    }
};