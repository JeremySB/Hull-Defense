// Created by Samuel Casteel

#pragma once

#include "Entity.h"
#include <stack>

class Enemy: public Entity{
public:
	Enemy();
	~Enemy();
	//void initialize();
	void update(float frameTime);
	//void attack();
	void setPath(std::stack<VECTOR2> path){this->path=path;};
	Entity* getTarget(){ return target;}
	void setTarget(Entity* target){ this->target = target;}

private:
	float speed;
    std::stack<VECTOR2> path;
	Entity* target;
};
