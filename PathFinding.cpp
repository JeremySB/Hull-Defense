#include "PathFinding.h"
#include <iostream>

//#include "Display.h"

std::stack<int*>  PathFinding::backstep() {
	// the stack to return
    std::stack<int*> *ret = new std::stack<int*>;
    // the starting point of our list
	int *tmp=new int[2];

    tmp[0]=path.top().coordinates[0];
    tmp[1]=path.top().coordinates[1];
    
	ret->push(tmp);//path.top().coordinates);
    
	this->path.pop();
	this->map[tmp[0]][tmp[1]] = -this->map[tmp[0]][tmp[1]]; //?
    // goes through the path we found earlier
	while (!path.empty()) {
		// makes sure the tiles are only one away from eachother
        if ((/*this->path.top().coordinates[0] == ret->top()[0] && */ abs(this->path.top().coordinates[1] - ret->top()[1]) == 1) ||
            (/*this->path.top().coordinates[1] == ret->top()[1] && */ abs(this->path.top().coordinates[0] - ret->top()[0]) == 1)) {
            tmp[0]=path.top().coordinates[0];
            tmp[1]=path.top().coordinates[1];
            ret->push(tmp);
			this->map[tmp[0]][tmp[1]] = -this->map[tmp[0]][tmp[1]];
        }
        this->path.pop();
    }
	
	while(!discovered.empty()){
		Tile loc = *discovered.top();
		discovered.pop();
		this->map[loc.coordinates[0]][loc.coordinates[1]]=0;
	}
    
	delete[] tmp;
    return *ret;
}

Tile PathFinding::generateTile(int y,int x, Entity* target){
    Tile *tmp = new Tile();
    tmp->coordinates[0]=y;
    tmp->coordinates[1]=x;
	tmp->weight = this->map[x][y] * (pow(y-grid->gridYLoc(target->getY()),2)+pow(x-grid->gridXLoc(target->getX()),2));
    //this->map->board[y][x]=-1;
	this->map[y][x] = -this->map[y][x];
    return *tmp;
}


std::stack<int *> PathFinding::findPath(Entity* target) {
	while(!nextStep(target));
	return backstep();
}

bool PathFinding::nextStep(Entity* target){
	// if the list of discovered values is empty you cannot reach your target
	if(discovered.empty()){
		std::cout<<"empty"<<std::endl;
		return true;
	}
	// we get the lowest cost tile off of the queue
    Tile prev=*discovered.top();
	discovered.pop();
	// we push it onto the path list that we have
    this->path.push(prev);
	this->map[prev.coordinates[0]][prev.coordinates[1]] = -this->map[prev.coordinates[0]][prev.coordinates[1]];
	// if the weight is 0 we have reached our target
    if(prev.weight==0){
        return true;
    }
    discoverAdjacent(prev.coordinates,target);
    return false;
}

void PathFinding::discoverAdjacent(int coor[2],Entity* target){
	// discover all adjacent tiles
	for(int x = (coor[0]-1 < 0 ? 0 : coor[0]-1); x < coor[0] + 2 && x < GRID_WIDTH; x++){
		for(int y = (coor[1]-1 < 0 ? 0 : coor[1]-1); y < coor[1]+2 && y < GRID_HEIGHT; y++){
			if(!(x == coor[0] && y == coor[0])){
				if( map[x][y] > 0){
					this->discovered.push(&generateTile(x,y,target));
				}
			}
		}
	} 
}

void PathFinding::loadMap(StructureGrid* grid){
	// load up the map from a structure grid and get values for the array
	this->grid = grid;
	this->map = new int*[GRID_WIDTH];//size()];//=map;
	for( int x = 0; x < GRID_WIDTH; x++){
		map[x] = new int[GRID_HEIGHT];
		for( int y = 0; y < GRID_HEIGHT; y++){
			Structure* tmp = grid->atGridCoords(x,y);
			if(tmp == nullptr)
				map[x][y] = 1;
			else{
				map[x][y] = tmp->getType();
				/*switch(tmp->getType(x,y)){
				case(Wall):
					map[x][y] = 2;
					break;
				case(Tower):
					map[x][y] = 3;
					break;
				}*/
			}
		}
	}
	while(!discovered.empty())
		discovered.pop();
	//this->discovered.push/*Sort*/(&generateTile(GRID_HEIGHT/2,0));
}

bool operator<(Tile first,Tile second){
    return first.weight<second.weight;
}

bool operator>(Tile first, Tile second) {
    return first.weight>second.weight;
}
