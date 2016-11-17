#include "PathFinding.h"
#include <iostream>

//#include "Display.h"

std::stack<VECTOR2>  PathFinding::backstep() {
	// the stack to return
    std::stack<VECTOR2> *ret = new std::stack<VECTOR2>;
    // the starting point of our list
	//int *tmp=new int[2];
    this->map[(int)path.top().coordinates.x][(int)path.top().coordinates.y] *= -1;//abs(-this->map[(int)tmp.x][(int)tmp.y]); //?
    this->path.pop();
	VECTOR2 tmp( (path.top().coordinates.x * CELL_WIDTH)+CELL_WIDTH/2,
	             (path.top().coordinates.y * CELL_HEIGHT)+CELL_HEIGHT/2);
    
	ret->push(tmp);//path.top().coordinates);
    this->map[(int)path.top().coordinates.x][(int)path.top().coordinates.y] *= -1;//abs(-this->map[(int)tmp.x][(int)tmp.y]); //?
	this->path.pop();

    // goes through the path we found earlier
	while (!path.empty()) {
		// makes sure the tiles are only one away from eachother

        if (( abs(this->path.top().coordinates[1] - ret->top()[1]) == 1) ||
            ( abs(this->path.top().coordinates[0] - ret->top()[0]) == 1)) {
            tmp = VECTOR2((path.top().coordinates.x * CELL_WIDTH) + CELL_WIDTH / 2,
                (path.top().coordinates.y * CELL_HEIGHT) + CELL_HEIGHT / 2);
            ret->push(tmp);
        }
        
        this->map[(int)path.top().coordinates.x][(int)path.top().coordinates.y] *= -1;
        this->path.pop();
    }
	
	while(!discovered.empty()){
		Tile loc = *discovered.top();
		discovered.pop();
		this->map[(int)loc.coordinates.x][(int)loc.coordinates.y] = abs(this->map[(int) loc.coordinates.x][(int) loc.coordinates.y]);
	}
    
	//delete[] tmp;
    return *ret;
}

Tile* PathFinding::generateTile(VECTOR2 coor, Entity* to){
    Tile *tmp = new Tile();
    tmp->coordinates.y=coor.y;
    tmp->coordinates.x=coor.x;
	//tmp->weight = this->map[(int)coor.x][(int)coor.y] * ( pow( coor.y - to->getCenterY() / CELL_HEIGHT, 2 ) +pow( coor.x - to->getCenterX() / CELL_WIDTH, 2 ) );
    tmp->weight = PATHFINDING_MODIFIER * this->map[(int)coor.x][(int)coor.y]; //* 
    tmp->weight += sqrt(pow(coor.y * CELL_HEIGHT - to->getCenterY(), 2) + pow(coor.x * CELL_WIDTH - to->getCenterX(), 2));
	this->map[(int)coor.x][(int)coor.y] = -this->map[(int)coor.x][(int)coor.y];
    return tmp;
}


std::stack<VECTOR2> PathFinding::findPath(Entity* from, Entity* to) {
	while(!discovered.empty())
		discovered.pop();
	this->discovered.push(generateTile( VECTOR2(from->getCenterX() / CELL_WIDTH, from->getCenterY() / CELL_HEIGHT), to ));
    map[(int) from->getCenterX() / CELL_WIDTH][(int)from->getCenterY() / CELL_HEIGHT] *= -1;
    int counter = 0;
	while(!nextStep(to))
        counter++;
	return backstep();
}

bool PathFinding::nextStep(Entity* to){
	// if the list of discovered values is empty you cannot reach your to
	if(discovered.empty()){
		std::cout<<"empty"<<std::endl;
		return true;
	}
	// we get the lowest cost tile off of the queue
    Tile prev=*discovered.top();
	discovered.pop();
	// we push it onto the path list that we have
    this->path.push(prev);
	this->map[(int)prev.coordinates.x][(int)prev.coordinates.y] = -this->map[(int)prev.coordinates.x][(int)prev.coordinates.y];
	// if the weight is 0 we have reached our to
    if(prev.weight==0){
        return true;
    }
    discoverAdjacent(prev.coordinates,to);
    return false;
}

void PathFinding::discoverAdjacent(VECTOR2 coor,Entity* to){
	// discover all adjacent tiles
	for(int x = (coor.x-1 < 0 ? 0 : coor.x-1); x < coor.x + 1 && x < GRID_WIDTH; x++){
		for(int y = (coor.y-1 < 0 ? 0 : coor.y-1); y < coor.y + 1 && y < GRID_HEIGHT; y++){
			if(!(x == coor.x && y == coor.y)){
				if( map[x][y] > 0){
					this->discovered.push(generateTile(VECTOR2(x,y),to));
				}
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
