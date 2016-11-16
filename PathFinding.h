#pragma once
#ifndef _PATH_FINDING_
#define _PATH_FINDING_
#include <stack>
//#include "DLL.h"
#include "structureGrid.h"
#include <queue>
// 0 is empty
// 1 is a wall
// 2 is the start
// 3 is the end
/*template<class T>
struct ptr_less
    : public binary_function<T, T, bool> {  
        bool operator()(const T& left, const T& right) const{
            return ((left->weight) <( right->weight));
        }
};*/

// std::priority_queue<MyClass*, vector<MyClass*>, ptr_less<MyClass*> > que; 
struct Tile {
    int coordinates[2];
    double weight;
};

class PathFinding {
public:
    std::stack<int*> backstep();
	std::stack<int*> findPath(Entity* target);
    bool nextStep(Entity* target);
    void discoverAdjacent(int coor[2], Entity* target);
//    void loadMap(int map[7][6],int x,int y);
	void loadMap(StructureGrid *map);
	Tile generateTile(int y,int x, Entity* target);

private:
//	DoublyLinkedList<Tile> discovered;
	std::priority_queue<Tile*> discovered;//, std::vector<Tile*>, ptr_less<Tile*>> discovered;
	//std::vector<std::vector<Structure*>> 
	StructureGrid* grid;
	int **map;
    std::stack<Tile> path;
    int start[2];
    int end[2];

};
#endif