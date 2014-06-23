#include "ParticleVector.h"

ParticleVector::ParticleVector() {}

ParticleVector::ParticleVector(Renderer* r, double limit) : r(r), limit(limit) {
	for (int i = 0; i < 100; i++){
		while (true){
			Particle q = Particle(20 + 60 * (i % 10), 20 + 40 * (i / 10), (rand() % 100) - 50, (rand() % 100) - 50, rand() % 20 + 10, 12, rand() % 256, rand() % 256, rand() % 256, 128 + rand() % 128);
			bool reset = false;
			for (int j = 0; j < i; j++){
				if (q.collision(particles[j])) {
					reset = true;
					continue;
				}
			}
			if (reset) continue;
			particles.push_back(q);
			break;
		}
	}
	for (auto &p : particles) predict(&p);
	pq.push(Event(0, nullptr, nullptr));
}

void ParticleVector::predict(Particle *a) {
	if (a == nullptr) return;

	// particle-particle collisions
	for (auto &b : particles) {
		double dt = a->timeToHit(b);
		if (t + dt <= limit)
			pq.push(Event(t + dt, a, &b));
	}

	double dtX = a->timeToHitVerticalWall();
	double dtY = a->timeToHitHorizontalWall();
	if (t + dtX <= limit) pq.push(Event(t + dtX, a, nullptr));
	if (t + dtY <= limit) pq.push(Event(t + dtY, nullptr, a));
}

void ParticleVector::draw() {
	for (auto &p : particles) {
		p.draw(r);
	}
}