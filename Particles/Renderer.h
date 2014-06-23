#pragma once
#include <SDL.h>
#include "Globals.h"
class Renderer
{
public:
	Renderer();
	~Renderer();
	SDL_Window *getWindow() { return window; }
	SDL_Renderer *getRenderer() { return renderer; }
	
	void fillRect(int x, int y, int w, int h, Uint32 color);
	void fillCircle(int x, int y, int radius, int r, int g, int b, int a);
	void clearScreen(int r, int g, int b);
	void renderPresent();
	int colour(int r, int g, int b);


private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_RendererInfo info;
};
