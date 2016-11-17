#include "Enemy.h"


void initialize();
void Enemy::update(float frameTime){
	VECTOR2 distance = *this->getCenter() - this->path.top();
	if ( pow(distance.x,2)+pow(distance.y,2) < 100){
		path.pop();
		distance = *this->getCenter() - this->path.top();
	}
	D3DXVec2Normalize(&distance,&distance);
	
}
void attack(){

}