// Created by Samuel Casteel

#pragma once
#ifndef _PATH_FINDING_
#define _PATH_FINDING_
#include <stack>
#include "structureGrid.h"
#include "structureManager.h"
#include <queue>


enum TileState  {Empty, OpenSet, ClosedSet};
struct INTVECTOR2{
    INTVECTOR2(int x,int y):x(x),y(y){}
    INTVECTOR2():x(0),y(0){}
    int x,y;
};

struct Tile {
    Tile():parent(nullptr),set(Empty),g(std::numeric_limits<float>::infinity()),h(0),f(0){}
    INTVECTOR2 coordinates;
    float g,h,f;
    Tile* parent;
    TileState set;
    StructureTypes modifier;
};

struct Target {
    INTVECTOR2 coordinates;
    StructureTypes type;
};

class less {
public:
    bool operator()(const Tile* left, const Tile* right) {
        return (left->f > right->f);
    }

};
class PathFinding {
public:
    PathFinding();
	~PathFinding();
    std::stack<VECTOR2> backstep();
	std::stack<VECTOR2> findPath(Entity* from, Entity* to);
    bool nextStep();
    void discoverAdjacent(Tile* parent);
	void loadMap(StructureGrid *map);
    void updateMap();
	Tile* updateTile(INTVECTOR2 coor, float g,Tile* parent);
    void PathFinding::resetValues();

private:
    Tile* getBestOpen();
    Tile* last;
	//std::priority_queue<Tile*,std::vector<Tile *>,less> openSet;
    StructureGrid* grid;
    //Entity *to;
    Target tar;
    Tile map[GRID_WIDTH][GRID_HEIGHT];
};
#endif