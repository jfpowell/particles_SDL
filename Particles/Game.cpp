#include "Game.h"

Game::Game() {
	limit = 10000;
	initParticles();
	eventLoop();
}

Game::~Game() {

}

void Game::initParticles(){
	for (int i = 0; i < 32; i++){
		for (int j = 0; j < 20; j++){
			int r = 255;
			int g = 0;
			int b = 0;
			int a = 255;
			if (i > 16) {
				r = 0;
				b = 255;
				if (j > 10) {
					g = 255;
					b = 0;
				}
			}
			else{
				if (j > 10) {
					r = rand()%256;
					g = rand() % 256;
					b = rand() % 256;
				}
			}
			Particle *q = new Particle(
				i*32+16,
				j*32+16,
				rand() % 200 - 100,
				rand() % 200 - 100,
				rand() % 20 + 10,
				rand() % 12 + 3,
				r,g,b,a);
			particles.push_back(q);
		}
	}

	for (auto p : particles) predict(p);

	pq.push(Event(0, nullptr, nullptr));
}

void Game::eventLoop() {
	SDL_Event event;
	bool running = true;

	while (running && !pq.empty()) {
		//Fill the surface white
		if (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT)
				running = false;
		}

		Event e = pq.top();
		pq.pop();
		if (!e.isValid()) continue;
		Particle *a = e.a;
		Particle *b = e.b;

		for (auto p : particles) {
			p->update(e.time - t);
		}
		t = e.time;

		if		(a != nullptr && b != nullptr) a->bounceOff(*b);              // particle-particle collision
		else if (a != nullptr && b == nullptr) 
			a->bounceOffVerticalWall();   // particle-wall collision
		else if (a == nullptr && b != nullptr) 
			b->bounceOffHorizontalWall(); // particle-wall collision
		else if (a == nullptr && b == nullptr) 
			redraw();               // redraw event

		predict(a);
		predict(b);
	}
}

void Game::predict(Particle *a) {
	if (a == nullptr) return;

	// particle-particle collisions
	for (auto b : particles) {
		double dt = a->timeToHit(b);
		if (t + dt <= limit){
			//std::cout << "Inserting element t = " << t + dt << std::endl;
			pq.push(Event(t + dt, a, b));
		}

	}

	double dtX = a->timeToHitVerticalWall();
	double dtY = a->timeToHitHorizontalWall();

	if (t + dtX <= limit) 
		pq.push(Event(t + dtX, a, nullptr));
	if (t + dtY <= limit) 
		pq.push(Event(t + dtY, nullptr, a));
}

void Game::redraw() {
	r.clearScreen(0xFF, 0xFF, 0xFF);
	for (auto p : particles) {
		p->draw(r);
	}
	r.renderPresent();
	if (t < limit) {
		pq.push(Event(t + 1/60.0, nullptr, nullptr));
	}
}