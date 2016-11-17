#include "EnemyManager.h"


void EnemyManager::addChild(Enemy* toAdd){
	children[numChildren++] = toAdd;
}

Enemy** EnemyManager::getChildren(){
	return children;
}

void EnemyManager::removeChild(Enemy* toRemove){
	bool deleted = false;
	for(int i = 0; i < numChildren; i++){
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
	for( int i = 0; i < numChildren; i++){
		children[i]->path = pathFinder.findPath(reinterpret_cast<Entity*>(children[i]),reinterpret_cast<Entity *>(children[i]->getTarget())); 
	}
}