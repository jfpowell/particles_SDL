#include<limits>
#include "Particle.h"
#include "Globals.h"
#include "Renderer.h"

Particle::Particle() {};

Particle::Particle(int xPos, int yPos, int xVel, int yVel, int charge, int radius, int r, int g, int b, int a) : 
	xPos(xPos), yPos(yPos), xVel(xVel), yVel(yVel), charge(charge), radius(radius), r(r), g(g), b(b), a(a) { 
	mass = pow(radius, 2); 
	count = 0;
};
void Particle::draw(Renderer &rend) {
	rend.fillCircle((int)(xPos), (int)(yPos), radius, r, g, b, a);
}
void Particle::update(double dt) {
	xPos += xVel*dt;
	yPos += yVel*dt;
}
int Particle::getCount() { return count; }
double Particle::timeToHit(Particle *that) {
	if (this == that) return std::numeric_limits<double>::infinity();
	double dx = that->xPos - xPos;
	double dy = that->yPos - yPos;
	double dvx = that->xVel - xVel;
	double dvy = that->yVel - yVel;
	double dvdr = dx*dvx + dy*dvy;
	if (dvdr > 0) return std::numeric_limits<double>::infinity();
	double dvdv = dvx*dvx + dvy*dvy;
	double drdr = dx*dx + dy*dy;
	double sigma = radius + that->radius;
	double d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
	// if (drdr < sigma*sigma) StdOut.println("overlapping particles");
	if (d < 0) return std::numeric_limits<double>::infinity();
	return -(dvdr + sqrt(d)) / dvdv;
}
double Particle::distanceSquared(Particle &that){
	return pow(that.xPos - xPos, 2) + pow(that.yPos - yPos, 2);
}
double Particle::distance(Particle & that) {
	return sqrt(distanceSquared(that));
}
double Particle::velocitySquared(){
	return pow(xVel, 2) + pow(yVel, 2);
}
double Particle::energy(){
	return 0.5 * velocitySquared();
}
bool Particle::collision(Particle &that){
	double dx = that.xPos - xPos;
	double dy = that.yPos - yPos;
	double dist = sqrt(pow(dx, 2) + pow(dy, 2));
	return dist <= radius + that.radius;

}
void Particle::bounceOff(Particle &that){
	double dx = that.xPos - xPos;
	double dy = that.yPos - yPos;
	double dvx = that.xVel - xVel;
	double dvy = that.yVel - yVel;
	double dvdr = dx*dvx + dy*dvy;             // dv dot dr
	double dist = radius + that.radius;   // distance between particle centers at collison

	// normal force F, and in x and y directions
	double F = 2 * mass * that.mass * dvdr / ((mass + that.mass) * dist);
	double fx = F * dx / dist;
	double fy = F * dy / dist;

	// update velocities according to normal force
	xVel += fx / mass;
	yVel += fy / mass;
	that.xVel -= fx / that.mass;
	that.yVel -= fy / that.mass;

	// update collision counts
	count++;
	that.count++;
}

// update velocity of this particle upon collision with a vertical wall
void Particle::bounceOffVerticalWall() {
	xVel = -xVel;
	count++;
}

// update velocity of this particle upon collision with a horizontal wall
void Particle::bounceOffHorizontalWall() {
	yVel = -yVel;
	count++;
}

double Particle::timeToHitVerticalWall() {
	if (xVel > 0) return (SCREEN_WIDTH - xPos - radius) / xVel;
	else if (xVel < 0) return (radius - xPos) / xVel;
	else             return std::numeric_limits<double>::infinity();
}

double Particle::timeToHitHorizontalWall() {
	if (yVel > 0) return (SCREEN_HEIGHT - yPos - radius) / yVel;
	else if (yVel < 0) return (radius - yPos) / yVel;
	else             return std::numeric_limits<double>::infinity();
}