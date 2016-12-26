// Created by Samuel Casteel
#pragma once

#include "enemy.h"

class MediumEnemy : public Enemy {
public:
    MediumEnemy() {
        speed = 90;
        value = 75;
        health = 75;
        damage = 50;
        targeting = baseTarget;
        colorFilter = SETCOLOR_ARGB(255, 0, 125, 0);
    }
};