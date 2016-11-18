// Created by Samuel Casteel

#pragma once

#include "Entity.h"
#include <stack>



class Enemy: public Entity{
public:
    //Enemy(EnemyData data);
	Enemy();
	~Enemy();
	//void initialize();
	void update(float frameTime);
	//void attack();
	void setPath(std::stack<VECTOR2> path){this->path=path;};
	Entity* getTarget(){ return target;}
	void setTarget(Entity* target){ this->target = target;}
    Targeting getTargeting(){ return targeting;}
    void collidedThisFrame(){didCollideThisFrame = true;};
    int getDamage(){return damage;}
    int getValue(){return value;}
protected:
	float speed;
    int damage,value;
    Targeting targeting;
private:
    bool didCollideThisFrame;
    std::stack<VECTOR2> path;
	Entity* target;
    bool right;
};
