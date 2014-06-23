#pragma once
#include <SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <cstdlib>
#include <memory>
#include <cassert>

#include "Particle.h"
#include "Renderer.h"
#include "Event.h"

#include "Globals.h"
class Game
{
public:
	Game();
	~Game();
private:
	Renderer r;
	std::vector<Particle*> particles;
	std::priority_queue<Event> pq;
	double t = 0.0;
	double hz = 0.5;
	double limit;

	void initParticles();
	void eventLoop();
	void update();
	void redraw();
	void predict(Particle *a);
};