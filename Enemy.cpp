// Created by Samuel Casteel
#include "Enemy.h"

Enemy::Enemy():target(nullptr),didCollideThisFrame(false),right(false){

}
Enemy::~Enemy(){

}
void Enemy::update(float frameTime){
    if(this->path.empty())
        return;
	if(didCollideThisFrame){
        setRadians(getRadians() + PI / 16 * (right ? -1 : 1) );
        right = !right;	
		didCollideThisFrame = false;
		return;
	}

	VECTOR2 distance = *this->getCenter() - this->path.top();
	if ( pow(distance.x,2)+pow(distance.y,2) < 10){
        path.pop();
        if(this->path.empty())
            return;
		distance = *this->getCenter() - this->path.top();
	}
    distance =- distance;
	D3DXVec2Normalize(&distance,&distance);
    setRadians(getRadians()+angleToTarget(this->path.top()) - PI/2);
	setX(getX() + distance.x * speed * frameTime);
    setY(getY() + distance.y * speed * frameTime);
}

/*void Enemy::attack(){


}*/