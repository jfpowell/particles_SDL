#pragma once

#include "Particle.h"

class Event
{
public:
	double time;
	Particle * a;
	Particle * b;
	int countA, countB;

	Event(Event&& other) : time(other.time), a(other.a), b(other.b), countA(other.countA), countB(other.countB) {}
	Event& operator=(const Event& other) { 
		time = other.time;
		a = other.a;
		b = other.b;
		countA = other.countA;
		countB = other.countB;

		return *this;
	}
	Event(double t, Particle *a, Particle *b);
	~Event();
	bool operator< (const Event &r) const {
		return time > r.time;
	}
	bool isValid();
};

