#include "Event.h"


Event::Event(double t, Particle *a, Particle *b) : time(t), a(a), b(b), countA(a != nullptr ? a->getCount() : -1), countB(b != nullptr ? b->getCount() : -1) {}

Event::~Event()
{
}

bool Event::isValid(){
	if (a != nullptr && a->getCount() != countA) return false;
	if (b != nullptr && b->getCount() != countB) return false;
	return true;
}
