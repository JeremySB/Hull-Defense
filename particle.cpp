#include "particle.h"



Particle::Particle() : Image()
{
	active = false;
	visible = false;
	velocity = VECTOR2(0, 0);
}


Particle::~Particle()
{
	Image::~Image();
}

void Particle::update(float frameTime)
{
	timeToLive -= frameTime;

	if (timeToLive <= 0)
	{
		active = false;
		visible = false;
		timeToLive = 0;
		return;
	}
	
	Image::update(frameTime);
    ;
    //this->setColorFilter(SETCOLOR_ARGB(255 * (int) ((timeToLive / maxTimeToLive)), 128, 128, 128));
	setX(getX() + velocity.x * frameTime);
	setY(getY() + velocity.y * frameTime);
}
