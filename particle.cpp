#include "particle.h"



Particle::Particle() : Image()
{
	active = false;
	visible = false;
}


Particle::~Particle()
{
	Image::~Image();
}

void Particle::update(float frameTime)
{
	Image::update(frameTime);
	timeToLive -= frameTime;

	if (timeToLive <= 0)
	{
		active = false;
		visible = false;
		timeToLive = 0;
	}
}
