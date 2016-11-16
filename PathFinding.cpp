#include "PathFinding.h"
#include <iostream>

//#include "Display.h"

std::stack<int*>  PathFinding::backstep() {
    std::stack<int*> *ret = new std::stack<int*>;
    int *tmp=new int[2];

    tmp[0]=path.top().coordinates[0];
    tmp[1]=path.top().coordinates[1];
    
	ret->push(tmp);//path.top().coordinates);
    
	this->path.pop();
	this->map[tmp[0]][tmp[1]]=-3; //?
    
	while (!path.empty()) {
        if ((this->path.top().coordinates[0] == ret->top()[0] && abs(this->path.top().coordinates[1] - ret->top()[1]) == 1) ||
            (this->path.top().coordinates[1] == ret->top()[1] && abs(this->path.top().coordinates[0] - ret->top()[0]) == 1)) {
            tmp[0]=path.top().coordinates[0];
            tmp[1]=path.top().coordinates[1];
            ret->push(tmp);
			this->map->board[tmp[0]][tmp[1]]=-3;
        }
        this->path.pop();
    }
	
	while(!discovered.empty()){
		Tile loc = *discovered.top();
		discovered.pop();
		this->map->board[loc.coordinates[0]][loc.coordinates[1]]=0;
	}
    
	delete[] tmp;
    return *ret;
}

Tile PathFinding::generateTile(int y,int x, Structure* target){
    Tile *tmp = new Tile();
    tmp->coordinates[0]=y;
    tmp->coordinates[1]=x;
    tmp->weight=sqrt(pow(y-this->map->end[0],2)+pow(x-this->map->end[1],2));
    //this->map->board[y][x]=-1;
    return *tmp;
}


std::stack<int *> PathFinding::findPath(Structure* target) {
	while(!nextStep(target));
	return backstep();
}

bool PathFinding::nextStep(Entity* target){
	if(discovered.empty()){
		std::cout<<"empty"<<std::endl;
		return true;
	}
    Tile prev=*discovered.top();
	discovered.pop();
    this->path.push(prev);
    this->map->board[prev.coordinates[0]][prev.coordinates[1]]=-2;
    if(prev.weight==0){
        return true;
    }
    discoverAdjacent(prev.coordinates);
    return false;
}

void PathFinding::discoverAdjacent(int coor[2]){
	if(coor[1]-1>=0 && 
		(!map->board[coor[0]][coor[1]-1] || (map->end[0]==coor[0] && map->end[1]==coor[1]-1))){
		this->discovered.push/*Sort*/(&generateTile(coor[0],coor[1]-1));
		this->map->board[coor[0]][coor[1]-1]=-1;
	}

	if(coor[1]+1<this->map->getX() && 
		(!map->board[coor[0]][coor[1]+1] || (map->end[0]==coor[0] && map->end[1]==coor[1]+1))){
		discovered.push/*Sort*/(&generateTile(coor[0],coor[1]+1));
		this->map->board[coor[0]][coor[1]+1]=-1;
	}

	if(coor[0]-1>=0 && 
		(!map->board[coor[0]-1][coor[1]] || (map->end[0]==coor[0]-1 && map->end[1]==coor[1]))){
		discovered.push/*Sort*/(&generateTile(coor[0]-1,coor[1]));
		this->map->board[coor[0]-1][coor[1]]=-1;
	}

	if(coor[0]+1<this->map->getY() && 
		(!map->board[coor[0]+1][coor[1]] || (map->end[0]==coor[0]+1 && map->end[1]==coor[1]))){
		discovered.push/*Sort*/(&generateTile(coor[0]+1,coor[1]));
		this->map->board[coor[0]+1][coor[1]]=-1;
	}
}

void PathFinding::loadMap(std::vector<std::vector<Structure*>> map){
    this->map = new int[map.size()];//=map;
	while(!discovered.empty())
		discovered.pop();
	this->discovered.push/*Sort*/(&generateTile(this->map->start[0],this->map->start[1]));
}

bool operator<(Tile first,Tile second){
    return first.weight<second.weight;
}

bool operator>(Tile first, Tile second) {
    return first.weight>second.weight;
}
