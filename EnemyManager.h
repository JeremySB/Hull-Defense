#include "Enemy.h"
#include "PathFinding.h"

class EnemyManager{
public:
	EnemyManager();
	~EnemyManager();
	Enemy** getChildren();
	void addChild(Enemy *toAdd);
	void removeChild(Enemy *toRemove);
	void updateChildren(float frameTime);
	void findPaths();
private:
	Enemy* children[MAX_ENEMIES];
	unsigned int numChildren;
	PathFinding pathFinder;
};