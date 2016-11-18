// Created by Samuel Casteel

#pragma once

#include "Enemy.h"
#include "PathFinding.h"

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();
	Enemy** getChildren();
	void addChild(Enemy *toAdd);
	void removeChild(Enemy *toRemove);
	void updateChildren(float frameTime);
	void findPaths();
    void draw();
    void onLostDevice();
    void onResetDevice();
    void setGrid(StructureGrid* tmp){pathFinder.loadMap(tmp);}
private:
	Enemy* children[MAX_ENEMIES];
	unsigned int numChildren;
	PathFinding pathFinder;
    VECTOR2 spawn;
};