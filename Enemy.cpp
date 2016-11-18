#include "Enemy.h"
/*Enemy::Enemy(EnemyData data):speed(data.speed),damage(data.damage),targeting(data.toTarget){
    setHealth(data.health);
}*/
Enemy::Enemy():target(nullptr),didCollideThisFrame(false){

}
Enemy::~Enemy(){

}
void Enemy::update(float frameTime){
    if(this->path.empty())
        return;
	VECTOR2 distance = *this->getCenter() - this->path.top();
	if ( pow(distance.x,2)+pow(distance.y,2) < 100){//< 100){//5){
        path.pop();
        if(this->path.empty())
            return;
		distance = *this->getCenter() - this->path.top();
	}
    distance =- distance;
	D3DXVec2Normalize(&distance,&distance);
    setRadians(getRadians()+angleToTarget(this->path.top()) - PI/2);
    if(!didCollideThisFrame){
	    setX(getX() + distance.x * speed * frameTime);
        setY(getY() + distance.y * speed * frameTime);
    }
    else{
        VECTOR2();
    }
    didCollideThisFrame = false;
}

