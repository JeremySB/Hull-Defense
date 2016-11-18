// Created by Samuel Casteel

#pragma once
#include "Enemy.h"
#include "HeavyEnemy.h"
#include "MediumEnemy.h"
#include "LightEnemy.h"
#include "PathFinding.h"
#include "gameState.h"
#include <list>
class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();

    void initialize(Game* game, StructureGrid* grid,GameState* state,Audio* audio);

	std::list<Enemy*> getChildren();
	void addChild(Enemy *toAdd);
	void removeChild(Enemy *toRemove);
	void updateChildren(float frameTime);

	void findPaths();
    void draw();

    void onLostDevice();
    void onResetDevice();

    void setGrid(StructureGrid* tmp){grid = tmp; pathFinder.loadMap(tmp);}
    void updateStructures();
    void reset();
    VECTOR2 getSpawn(){return spawn;}
    void setSpawn(VECTOR2 tmp){spawn = tmp;}
    unsigned int getNumChildren(){return numChildren;}
private: 
    Game*game;
    GameState *state;
    StructureGrid* grid;
    TextureManager enemyTexture;
	Enemy* children[MAX_ENEMIES];
    Structure *strongest, *weakest, *base;
	unsigned int numChildren;
	PathFinding pathFinder;
	Audio* audio;
    VECTOR2 spawn;
};