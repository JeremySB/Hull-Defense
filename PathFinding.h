#pragma once
#ifndef _PATH_FINDING_
#define _PATH_FINDING_
#include <stack>
#include "structureGrid.h"
#include <queue>

struct Tile {
    VECTOR2 coordinates;
    float weight;
};
class less {
public:
    bool operator()(const Tile left, const Tile right) {
        return (left.weight > right.weight);
    }

};
class PathFinding {
public:
	~PathFinding();
    std::stack<VECTOR2> backstep();
	std::stack<VECTOR2> findPath(Entity* from, Entity* to);
    bool nextStep(Entity* target);
    void discoverAdjacent(Tile parent, Entity* to);
	void loadMap(StructureGrid *map);
    void updateMap();
	Tile generateTile(VECTOR2 coor, Entity* to,float parentWeight);

private:
	std::priority_queue<Tile,std::vector<Tile>,less> discovered;
    StructureGrid* grid;
	int **map;
    std::stack<Tile> path;

};
#endif