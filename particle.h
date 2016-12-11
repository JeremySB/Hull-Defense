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

	const VECTOR2 getVelocity() const { return velocity; }

	float getTimeToLive() { return timeToLive; }

	// set particle active or inactive
	// false hides it and particleManager won't use it
	void setActive(bool active) { 
		this->active = active;
		visible = active;
	}

	void setVelocity(VECTOR2 v) { velocity = v; }

	void setTimeToLive(float timeToLive) {
		this->timeToLive = timeToLive;
	}

protected:
	float timeToLive;
	bool active;
	VECTOR2 velocity;
};

