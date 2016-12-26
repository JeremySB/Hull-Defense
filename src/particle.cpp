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
	// fade a bit
	else if (timeToLive <= 0.1)
	{
		D3DCOLOR color = (getColorFilter() | (0xff << 24)) & SETCOLOR_ARGB(10, 255, 255, 255);
		setColorFilter(color);
	}
	else if (timeToLive <= 0.2)
	{
		D3DCOLOR color = (getColorFilter() | (0xff << 24)) & SETCOLOR_ARGB(30, 255, 255, 255);
		setColorFilter(color);
	}
	
	Image::update(frameTime);
    ;
    //this->setColorFilter(SETCOLOR_ARGB((int)(255 * ((timeToLive / maxTimeToLive))), 128, 128, 128));
	setX(getX() + velocity.x * frameTime);
	setY(getY() + velocity.y * frameTime);
}
