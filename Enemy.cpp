#include "Enemy.h"

Enemy::Enemy():speed(5){


}
Enemy::~Enemy(){

}
void Enemy::update(float frameTime){
    if(this->path.empty())
        return;
	VECTOR2 distance = *this->getCenter() - this->path.top();
	if ( pow(distance.x,2)+pow(distance.y,2) < 100){//5){
        path.pop();
        if(this->path.empty())
            return;
		distance = *this->getCenter() - this->path.top();
	}
    distance =- distance;
	D3DXVec2Normalize(&distance,&distance);
	setX(getX() + distance.x * speed * frameTime);
    setY(getY() + distance.y * speed * frameTime);
}

