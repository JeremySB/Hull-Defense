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
    updateStructures();
}


void EnemyManager::addChild(Enemy* toAdd){
    if (!toAdd->initialize(game, 0, 0, 0, &enemyTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
    toAdd->setX(spawn.x);
    toAdd->setY(spawn.y);
    toAdd->setScale(0.06);
    toAdd->setCollisionRadius(CELL_WIDTH/2);
    toAdd->activate();
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
    case(baseTarget):
        toAdd->setTarget(base);
        break;
    }
    if (toAdd->getTarget())
        toAdd->setPath(pathFinder.findPath(reinterpret_cast<Entity*>(toAdd), reinterpret_cast<Entity *>(toAdd->getTarget())));
}

std::list<Enemy*> EnemyManager::getChildren(){
    std::list<Enemy*> ret;
    for(int i = 0; i < MAX_ENEMIES && children[i] != nullptr; i++){
        ret.push_back(children[i]);
    }
    return ret;
}

void EnemyManager::removeChild(Enemy* toRemove){
	bool deleted = false;
	for(int i = 0; i < numChildren || (deleted && i+1 < numChildren); i++){
		if(children[i] == toRemove){
			delete children[i];
            numChildren--;
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
    std::list<Structure*> bob = grid->getStructures();

    //tmp.pop_front();
    for( int i = 0; i < numChildren; i++){
        std::list<Structure*> tmp = bob;
        while(!tmp.empty()){
            if(children[i]->collidesWith(*tmp.front(),VECTOR2())){
                tmp.front()->setHealth(tmp.front()->getHealth() - children[i]->getDamage() * frameTime);
                children[i]->collidedThisFrame();
                break;
            }
            //else{
		        //children[i]->update(frameTime);
            //}
            tmp.pop_front();
        }
        children[i]->update(frameTime);
        if (children[i]->getHealth() <= 0) {
            removeChild(children[i]);
            i--;
        }
    }
}
void EnemyManager::updateStructures(){
    std::list<Structure*> tmp = grid->getStructures();
    strongest = tmp.front();
    weakest = tmp.front();
    while (!tmp.empty()) {
        if (tmp.front()->getHealth() > strongest->getHealth())
            strongest = tmp.front();
        if (tmp.front()->getHealth() < weakest->getHealth())
            weakest = tmp.front();
        tmp.pop_front();
    }


}

void EnemyManager::findPaths(){
    updateStructures();
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