#pragma once
#include <SDL.h>
#include "Renderer.h"
class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void update(){};
	virtual void draw(double dt, Renderer* r){};
};

