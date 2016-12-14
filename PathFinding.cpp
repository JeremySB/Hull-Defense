// Created by Samuel Casteel
#include "PathFinding.h"
#include <iostream>

//#include "Display.h"

PathFinding::PathFinding(){
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            map[x][y] = Tile();
            map[x][y].coordinates = INTVECTOR2(x, y);
            map[x][y].modifier = StructureTypes::none;
        }
    }
}
PathFinding::~PathFinding(){
}

void PathFinding::resetValues(){
    last = nullptr;
    for(int x = 0; x < GRID_WIDTH; x++){
        for(int y = 0; y < GRID_HEIGHT; y++){
            map[x][y].set = Empty;
            map[x][y].g = std::numeric_limits<float>::infinity();
        }
    }
}

std::stack<VECTOR2>  PathFinding::backstep() {
	// the stack to return
    std::stack<VECTOR2> ret;
    // the starting point of our list
	VECTOR2 tmp;
    Tile* top = getBestOpen();
    while(top){
        VECTOR2 tmp = VECTOR2((top->coordinates.x * CELL_WIDTH) + CELL_WIDTH / 2,
            (top->coordinates.y * CELL_HEIGHT) + CELL_HEIGHT / 2);
        ret.push(tmp);
        top = top->parent;
    }
    // goes through the path we found earlier
    if(!ret.empty())
        ret.pop();
    return ret;
}


std::stack<VECTOR2> PathFinding::findPath(Entity* from, Entity* to) {
    tar.coordinates.x = (to->getCenterX() / CELL_WIDTH);
    tar.coordinates.y = (to->getCenterY() / CELL_HEIGHT);
    resetValues();
	int x =(int)(from->getCenterX() / CELL_WIDTH);
	int y = (int)(from->getCenterY() / CELL_HEIGHT);

	Tile* start = updateTile(INTVECTOR2(x, y), 0, nullptr);

    start->g = 0;

	while(!nextStep());
	return backstep();
}

bool PathFinding::nextStep(){
	// if the list of discovered values is empty you cannot reach your to
	// we get the lowest cost tile off of the queue
    Tile* current = getBestOpen();
    if(!current)
        return true;
    else if(current->h == 0)
        return true;

    current->set = ClosedSet;

    //this->map[(int)current->coordinates.x][(int)current->coordinates.x].set = Empty;
	// we push it onto the path list that we have
	// if the weight is 0 we have reached our target

    discoverAdjacent(current);
    return false;
}

Tile* PathFinding::updateTile(INTVECTOR2 coor, float g, Tile* parent) {//float parentWeight){
    Tile* tmp = &map[coor.x][coor.y];
    tmp->set = OpenSet;
    tmp->parent = parent;
    tmp->g = 0;
    tmp->h = 0;
    tmp->f = 0;
    tmp->g = g;
    tmp->h = sqrt( pow(coor.y - tar.coordinates.y, 2) + pow(coor.x  - tar.coordinates.x, 2));
    tmp->f = tmp->h + tmp->g;

    return tmp;
}

void PathFinding::discoverAdjacent(Tile* parent){
	// discover all adjacent tiles
	INTVECTOR2 coor = parent->coordinates;
	for(int x = (coor.x-1 < 0 ? 0 : coor.x-1); x <= coor.x + 1 && x < GRID_WIDTH; x++){
		for(int y = (coor.y-1 < 0 ? 0 : coor.y-1); y <= coor.y + 1 && y < GRID_HEIGHT; y++){
			// if the tile has been discovered in the past it is negated and so is skipped here
			if(map[x][y].set != ClosedSet  && map[x][y].modifier != permWall){
				int ydiff = coor.y - y;
				int xdiff = coor.x - x;

                float tmpg = (abs(ydiff)+abs(xdiff) == 2 ? 1.25 : 1) * map[x][y].modifier + parent->g;

                // if we are on one of the cardinal directions we just add them to the path
				if( 
                    (x == coor.x && y != coor.y) || 
                    (y == coor.y && x != coor.x) || 
                    ( map[x + xdiff][y].modifier == none && map[x][y + ydiff].modifier == none)){
                    if (map[x][y].modifier != OpenSet || tmpg < map[x][y].g){
					    updateTile(INTVECTOR2(x,y), tmpg, parent);
                    }
				}
			}
		}
	} 
}



void PathFinding::updateMap(){
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            Structure* tmp = grid->atGridCoords(x, y);
            if(tmp)
                map[x][y].modifier = tmp->getType();
            else
                map[x][y].modifier = StructureTypes::none;
        }
    }
    resetValues();
}
void PathFinding::loadMap(StructureGrid* grid){
	this->grid = grid;
    updateMap();
}

bool operator<(Tile first,Tile second){
    return first.f < second.f;
}

bool operator>(Tile first, Tile second) {
    return first.f > second.f;
}

Tile* PathFinding::getBestOpen(){
    Tile* ret = nullptr;
    for(int x = 0; x < GRID_WIDTH; x++){
        for(int y = 0; y < GRID_HEIGHT; y++){
            if(map[x][y].set == OpenSet && (!ret || ret->f > map[x][y].f || (ret->f == map[x][y].f && map[x][y].g < ret->g) ))
                ret = &map[x][y];
        }
    }
    return ret;
}
