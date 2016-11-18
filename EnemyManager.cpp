#include "EnemyManager.h"

EnemyManager::EnemyManager():numChildren(0),spawn(0, GAME_HEIGHT / 2),strongest(nullptr),weakest(nullptr),base(nullptr){
    for ( int i = 0; i < MAX_ENEMIES; i ++){
        children[i] = nullptr;
    }
}

void EnemyManager::initialize(Game* game,StructureGrid* grid){
    this->game = game;
    if (!enemyTexture.initialize(game->getGraphics(), ENEMY_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
    setGrid(grid);
    Enemy* tmp = new LightEnemy();//HeavyEnemy();
    if (!tmp->initialize(game, 0, 0, 0, &enemyTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
    findPaths();
    addChild(tmp);
}


void EnemyManager::addChild(Enemy* toAdd){
    toAdd->setX(spawn.x);
    toAdd->setY(spawn.y);
    toAdd->setScale(.06);
    if(numChildren < MAX_ENEMIES){
	    children[numChildren++] = toAdd;
    }
    switch(toAdd->getTargeting()){
    case(strongestTarget):
        toAdd->setTarget(strongest);
        break;
    case(weakestTarget):
        toAdd->setTarget(weakest);
        break;
    }
    if (toAdd->getTarget())
        toAdd->setPath(pathFinder.findPath(reinterpret_cast<Entity*>(toAdd), reinterpret_cast<Entity *>(toAdd->getTarget())));
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
    grid->getStructures();
    std::list<Structure*> tmp = grid->getStructures();
    strongest = tmp.front();
    weakest = tmp.front();
    while(!tmp.empty()){
        if(tmp.front()->getHealth() > strongest->getHealth())
            strongest = tmp.front();
        if(tmp.front()->getHealth() < weakest->getHealth())
            weakest = tmp.front();
        tmp.pop_front();
    }

    pathFinder.updateMap();
	for( int i = 0; i < numChildren; i++){
        if(children[i]->getTarget())
		    children[i]->setPath(pathFinder.findPath(reinterpret_cast<Entity*>(children[i]),reinterpret_cast<Entity *>(children[i]->getTarget()))); 
	}
}

void EnemyManager::draw(){
    for( int i = 0; i < numChildren; i++){
        if(children[i] != nullptr)
            children[i]->draw(children[i]->getColorFilter());
    }
}


void EnemyManager::onLostDevice(){
    enemyTexture.onLostDevice();
}
void EnemyManager::onResetDevice(){
    enemyTexture.onResetDevice();
}