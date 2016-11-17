#pragma once
#ifndef _PATH_FINDING_
#define _PATH_FINDING_
#include <stack>
#include "structureGrid.h"
#include <queue>
#include <algorithm>
// 1 is empty
// 2 is a wall
// 3 is a turret
// 4 is a tower

/*template<class T>
struct ptr_less
    : public binary_function<T, T, bool> {  
        bool operator()(const T& left, const T& right) const{
            return ((left->weight) <( right->weight));
        }
};*/

// std::priority_queue<MyClass*, vector<MyClass*>, ptr_less<MyClass*> > que; 

struct Tile {
    VECTOR2 coordinates;
    float weight;
};
class less {
public:
    bool operator()(const Tile* left, const Tile* right) {
        return (left->weight > right->weight);
    }

};
//auto cmp = [](Tile* left, Tile* right) { return (left->weight) < (right->weight); };
//std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
class PathFinding {
public:
    std::stack<VECTOR2> backstep();
	std::stack<VECTOR2> findPath(Entity* from, Entity* to);
    bool nextStep(Entity* target);
    void discoverAdjacent(Tile parent, Entity* to);
//    void loadMap(int map[7][6],int x,int y);
	void loadMap(StructureGrid *map);
    void updateMap();
	Tile* generateTile(VECTOR2 coor, Entity* to,float parentWeight);

private:
//	DoublyLinkedList<Tile> discovered;

	std::priority_queue<Tile*,std::vector<Tile*>,less> discovered;//, std::vector<Tile*>, ptr_less<Tile*>> discovered;
	//std::vector<std::vector<Structure*>> 
    StructureGrid* grid;
	int **map;
    std::stack<Tile> path;

};
#endif