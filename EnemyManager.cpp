// Created by Samuel Casteel
#include "EnemyManager.h"

EnemyManager::EnemyManager():numChildren(0),spawn(0, GAME_HEIGHT / 2),strongest(nullptr),weakest(nullptr),base(nullptr){
    for ( int i = 0; i < MAX_ENEMIES; i ++){
        children[i] = nullptr;
    }
}
void EnemyManager::reset(){
    for( int i = 0; i < numChildren; i++){
        delete children[i];
        children[i] = nullptr;
    }
    numChildren = 0;
    updateStructures();
    pathFinder.updateMap();
}

void EnemyManager::initialize(Game* game,StructureGrid* grid, GameState* state,Audio* audio, ParticleManager *particleMan){
    this->game = game;
	this->audio = audio;
	this->state = state;
	this->particleMan = particleMan;

    if (!enemyTexture.initialize(game->getGraphics(), ENEMY_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
    setGrid(grid);

}


void EnemyManager::addChild(Enemy* toAdd) {
    if (numChildren < MAX_ENEMIES) {
        children[numChildren++] = toAdd;
    }
    else{
        delete toAdd;
        return;
    }
    if (!toAdd->initialize(game, 555, 508, 7, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	
    toAdd->setX(spawn.x);
	toAdd->setY(spawn.y);
	toAdd->setScale(toAdd->getScale() * 0.06);
	toAdd->setCollisionRadius(CELL_WIDTH / 2);
	toAdd->activate();
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
	//updateStructures();
	if (toAdd->getTarget()) {
		toAdd->setPath(pathFinder.findPath(reinterpret_cast<Entity*>(toAdd), reinterpret_cast<Entity *>(toAdd->getTarget())));
	}
}

std::list<Enemy*> EnemyManager::getChildren(){
    std::list<Enemy*> ret;
    for(int i = 0; i < numChildren && children[i] != nullptr; i++){
        ret.push_back(children[i]);
    }
    return ret;
}

void EnemyManager::removeChild(Enemy* toRemove){
	bool deleted = false;
	for(int i = 0; i < numChildren || (deleted && i+1 < numChildren); i++){
		if(children[i] == toRemove){
            state->addCurrency(children[i]->getValue());
			particleMan->addEnemyDeath(children[i]);
			delete children[i];
			audio->playCue(SQUISH);
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
    for( int i = 0; i < numChildren; i++){
        std::list<Structure *>::iterator tmp = bob.begin();
        while(tmp != bob.end()){
            if((*tmp)->getType() != permWall && children[i]->collidesWith(*(*tmp),VECTOR2())){
                (*tmp)->damage(children[i]->getDamage() * frameTime);
                children[i]->collidedThisFrame();
                break;
            }
            ++tmp;
        }
        children[i]->update(frameTime);
        if (children[i]->getHealth() <= 0) {
            if(typeid(*children[i]) == typeid(PregnantEnemy)){
                for(int j = 0; j < 7; j++){
                    float tmp = (rand() % 100)/100.0f ;
                    this->spawn = VECTOR2(children[i]->getX(), children[i]->getY()) + VECTOR2( CELL_WIDTH * tmp, CELL_HEIGHT * (1-tmp));
                    this->addChild(new BabyEnemy);
                }
            }
            removeChild(children[i]);
            i--;
        }
    }
}
void EnemyManager::updateStructures(){
    std::list<Structure*> tmp = grid->getStructures();
    if(tmp.empty()){
        strongest = nullptr;
        weakest = nullptr;
        base = nullptr;
    }
    else{
        strongest = nullptr;
        weakest = nullptr;
        base = nullptr;
        while (!tmp.empty()) {
            Structure *front = tmp.front();
            tmp.pop_front();
			if(front->getType() != permWall && front->getType() != wall){
			    if (strongest == nullptr || strongest->getType() == StructureTypes::base ||
                    (front->getType() != StructureTypes::base && front->getHealth() / front->getMaxHealth() > strongest->getHealth() / strongest->getMaxHealth()))
                    strongest = front;

			    if (!weakest || weakest->getType() == StructureTypes::base  ||
                    (front->getType() != StructureTypes::base && front->getHealth() / front->getMaxHealth() < weakest->getHealth() / weakest->getMaxHealth()))
                    weakest = front;

                if(front->getType() == StructureTypes::base)
                    base = front;
                }
        }
    }
    for(int i = 0; i < numChildren; i++){
        switch (children[i]->getTargeting()) {
        case(strongestTarget):
            children[i]->setTarget(strongest);
            break;
        case(weakestTarget):
            children[i]->setTarget(weakest);
            break;
        case(baseTarget):
            children[i]->setTarget(base);
            break;
        }
    }

}

void EnemyManager::findPaths(){
    updateStructures();
    pathFinder.updateMap();
	for( int i = 0; i < numChildren; i++){
        if(children[i]->getTarget() != nullptr)
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