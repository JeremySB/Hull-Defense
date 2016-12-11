#pragma once
#include "image.h"
class Particle :
	public Image
{
public:
	Particle();
	~Particle();

	void update(float frameTime);

	bool getActive() { return active; }

	// set particle active or inactive
	// false hides it and particleManager won't use it
	void setActive(bool active) { 
		this->active = active;
		visible = active;
	}

	float getTimeToLive() {
		return timeToLive;
	}

	void setTimeToLive(float timeToLive) {
		this->timeToLive = timeToLive;
	}

protected:
	float timeToLive;
	bool active;
};

