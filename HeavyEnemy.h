// Created by Samuel Casteel
#pragma once
#include "Enemy.h"

class HeavyEnemy : public Enemy {
public:
    HeavyEnemy(){
        speed = 50;
        value = 75;
        health = 200;
        damage = 20;
        targeting = weakestTarget;
        colorFilter = SETCOLOR_ARGB(255,125,0,0);
    }
};