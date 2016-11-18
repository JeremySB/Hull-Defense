// Created by Samuel Casteel
#pragma once

#include "enemy.h"

class LightEnemy : public Enemy {
public:
    LightEnemy() {
        speed = 100;
        value = 30;
        health = 100;
        damage = 30;
        targeting = baseTarget;
        colorFilter = SETCOLOR_ARGB(255,0,0,125);
    }
};