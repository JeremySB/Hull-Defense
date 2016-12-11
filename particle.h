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
	void setActive(bool active) { this->active = active; }

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

