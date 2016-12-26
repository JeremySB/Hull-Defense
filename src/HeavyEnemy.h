// Created by Samuel Casteel
#pragma once
#include "Enemy.h"

class HeavyEnemy : public Enemy {
public:
    HeavyEnemy(){
        speed = 70;
        value = 100;
        health = 100;
        damage = 20;
        targeting = weakestTarget;
        colorFilter = SETCOLOR_ARGB(255,125,0,0);
    }
};