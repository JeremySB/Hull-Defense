#include "EnemyManager.h"

EnemyManager::EnemyManager():numChildren(0){
    for ( int i = 0; i < MAX_ENEMIES; i ++){
        children[i] = nullptr;
    }
}

void EnemyManager::addChild(Enemy* toAdd){
    if(numChildren < MAX_ENEMIES){
	    children[numChildren++] = toAdd;
    }
}

Enemy** EnemyManager::getChildren(){
	return children;
}

void EnemyManager::removeChild(Enemy* toRemove){
	bool deleted = false;
	for(int i = 0; i < numChildren || (deleted && i+1 < numChildren); i++){
		if(children[i] == toRemove){
			delete children[i];
			deleted = true;
		}
		if(deleted){
			children[i] = children[i+1];
		}
	}
}

EnemyManager::~EnemyManager(){
	for(int i = 0; i < numChildren; i++){
		delete children[i];
		children[i] = nullptr;
	}
}

void EnemyManager::updateChildren(float frameTime){
	for( int i = 0; i < numChildren; i++){
		children[i]->update(frameTime);
	}
}

void EnemyManager::findPaths(){
    pathFinder.updateMap();
	for( int i = 0; i < numChildren; i++){
		children[i]->setPath(pathFinder.findPath(reinterpret_cast<Entity*>(children[i]),reinterpret_cast<Entity *>(children[i]->getTarget()))); 
	}
}

void EnemyManager::draw(){
    for( int i = 0; i < numChildren; i++){
        if(children[i] != nullptr)
            children[i]->draw();
    }
}