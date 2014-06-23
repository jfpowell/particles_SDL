#pragma once
#include "Entity.h"
#include <SDL.h>
#include <cmath>
#include "Renderer.h"
class Particle : public Entity {
private:
	double xPos, yPos;
	double xVel, yVel;
	double charge;
	double mass;
	int count;
	int radius;
	int r,g,b,a;
public:
	Particle();
	Particle(int xPos, int yPos, int xVel, int yVel, int charge, int radius, int r, int g, int b, int a);
	void draw(Renderer &r);
	void update(double dt);
	int getCount();
	double timeToHit(Particle *that);
	double distanceSquared(Particle &that);
	double distance(Particle &that);
	double velocitySquared();
	double energy();
	bool collision(Particle &that);
	void bounceOff(Particle &that);
	void bounceOffVerticalWall();
	void bounceOffHorizontalWall();
	double timeToHitVerticalWall();
	double timeToHitHorizontalWall();
};
