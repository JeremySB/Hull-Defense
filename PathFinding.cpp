// Created by Samuel Casteel
#include "PathFinding.h"
#include <iostream>

//#include "Display.h"
PathFinding::~PathFinding(){
	for( int x = 0; x < GRID_WIDTH; x++){
		delete[] map[x];
	}
	delete[] map;
}
std::stack<VECTOR2>  PathFinding::backstep() {
	// the stack to return
    std::stack<VECTOR2> ret;
    // the starting point of our list
	VECTOR2 tmp;
	//path.pop();

    // goes through the path we found earlier
	while (!path.empty()) {
		// makes sure the tiles are only one away from eachother
        tmp = VECTOR2((int)(path.top().coordinates.x * CELL_WIDTH) + CELL_WIDTH / 2,
                (int)(path.top().coordinates.y * CELL_HEIGHT) + CELL_HEIGHT / 2);
		if (ret.empty() || 
			( abs((int)tmp.x - (int)ret.top().x) <= CELL_WIDTH) &&
			( abs((int)tmp.y - (int)ret.top().y) <= CELL_HEIGHT)) {

            ret.push(tmp);
        }
        
        this->map[(int)path.top().coordinates.x][(int)path.top().coordinates.y] *= -1;
        this->path.pop();
    }
	
	while(!discovered.empty()){
		Tile loc = discovered.top();
		this->map[(int)discovered.top().coordinates.x][(int)discovered.top().coordinates.y] *= -1;
		discovered.pop();
	}
    ret.pop();
    return ret;
}

Tile PathFinding::generateTile(VECTOR2 coor, Entity* to,float parentWeight){
    Tile tmp;

	tmp.coordinates.y=coor.y;
    tmp.coordinates.x=coor.x;

    tmp.weight = pow(((int)coor.y) - (int)(to->getCenterY()/CELL_HEIGHT ), 2);
	tmp.weight += pow(((int)coor.x ) - (int)(to->getCenterX() / CELL_WIDTH), 2);
    tmp.weight *= this->map[(int) coor.x][(int) coor.y] * PATHFINDING_MODIFIER;
	
	this->map[(int)coor.x][(int)coor.y] *= -1;
    
	return tmp;
}


std::stack<VECTOR2> PathFinding::findPath(Entity* from, Entity* to) {
	while(!discovered.empty())
		discovered.pop();
	
	this->discovered.push(generateTile( VECTOR2( (int)(from->getCenterX() / CELL_WIDTH), (int)(from->getCenterY() / CELL_HEIGHT)), to,0 ));

    int counter = 0;
	while(!nextStep(to))
        counter++;
	return backstep();
}

bool PathFinding::nextStep(Entity* to){
	// if the list of discovered values is empty you cannot reach your to
	if(discovered.empty()){
		throw GameError::exception("Could not find path");
		return true;
	}
	// we get the lowest cost tile off of the queue
    Tile prev=discovered.top();
	discovered.pop();
	// we push it onto the path list that we have
    this->path.push(prev);
	// if the weight is 0 we have reached our to
    if(prev.weight==0){
        return true;
    }
    discoverAdjacent(prev,to);
    return false;
}

void PathFinding::discoverAdjacent(Tile parent,Entity* to){
	// discover all adjacent tiles
	VECTOR2 coor = parent.coordinates;
	for(int x = (coor.x-1 < 0 ? 0 : coor.x-1); x <= coor.x + 1 && x < GRID_WIDTH; x++){
		for(int y = (coor.y-1 < 0 ? 0 : coor.y-1); y <= coor.y + 1 && y < GRID_HEIGHT; y++){
			if(  map[x][y] > 0){
				this->discovered.push(generateTile(VECTOR2(x,y),to,parent.weight));
			}
		}
	} 
}
void PathFinding::updateMap(){
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            Structure* tmp = grid->atGridCoords(x, y);
            if (tmp == nullptr)
                map[x][y] = 1;
            else {
                map[x][y] = tmp->getType();
            }
        }
    }

}
void PathFinding::loadMap(StructureGrid* grid){
	// load up the map from a structure grid and get values for the array
	this->grid = grid;
	this->map = new int*[GRID_WIDTH];
    for (int x = 0; x < GRID_WIDTH; x++)
        map[x] = new int[GRID_HEIGHT];
    updateMap();
}

bool operator<(Tile first,Tile second){
    return first.weight<second.weight;
}

bool operator>(Tile first, Tile second) {
    return first.weight>second.weight;
}
