// Created by Samuel Casteel
#include "Enemy.h"

Enemy::Enemy():target(nullptr),didCollideThisFrame(false),right(false){

}
Enemy::~Enemy(){

}
void Enemy::update(float frameTime){

	if(didCollideThisFrame){
        //setRadians(getRadians() + PI / 16 * (right ? -1 : 1) );
        //right = !right;	
		didCollideThisFrame = false;

        setFrames(1, 6);
        setFrameDelay(.1);
        setCurrentFrame(6);
        setLoop(true);
		return;
	}
	if(this->path.empty())
       return;
    setFrames(0,0);
    setCurrentFrame(0);
	VECTOR2 distance = *this->getCenter() - this->path.top();
	if ( pow(distance.x,2)+pow(distance.y,2) < 1000){
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