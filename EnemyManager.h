// Created by Samuel Casteel

#pragma once

#include "Enemy.h"
#include "HeavyEnemy.h"
#include "MediumEnemy.h"
#include "LightEnemy.h"
#include "PathFinding.h"

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();

    void initialize(Game* game, StructureGrid* grid);

	Enemy** getChildren();
	void addChild(Enemy *toAdd);
	void removeChild(Enemy *toRemove);
	void updateChildren(float frameTime);

	void findPaths();
    void draw();

    void onLostDevice();
    void onResetDevice();

    void setGrid(StructureGrid* tmp){grid = tmp; pathFinder.loadMap(tmp);}
    void updateStructures();
private:
    Game* game;
    StructureGrid* grid;
    TextureManager enemyTexture;
	Enemy* children[MAX_ENEMIES];
    Structure *strongest, *weakest, *base;
	unsigned int numChildren;
	PathFinding pathFinder;
    VECTOR2 spawn;
};