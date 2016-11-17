#include "Entity.h"
#include <stack>

class Enemy: Entity{
public:
	Enemy();
	~Enemy();
	void initialize();
	void update(float frameTime);
	void attack();
	void getPath();
	Entity* getTarget(){ return target;}
	void setTarget(Entity* target){ this->target = target;}
	std::stack<VECTOR2> path;
private:
	float speed;

	Entity* target;
};
