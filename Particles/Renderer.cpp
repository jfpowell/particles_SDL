#include <iostream>
#include "Renderer.h"
#include <SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include <cassert>


Renderer::Renderer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow("Particles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetRendererInfo(renderer, &info);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	if (window == nullptr) {
		std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
	}
}


Renderer::~Renderer()
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Renderer::fillRect(int x, int y, int w, int h, Uint32 colour) {
	SDL_Rect rect = { x, y, w, h };
	//SDL_FillRect(screen, &rect, colour);
}

void Renderer::fillCircle(int x, int y, int radius, int r, int g, int b, int a){
	assert(filledCircleRGBA(renderer, x, y, radius, r, g, b, a) == 0);
}

void Renderer::clearScreen(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void Renderer::renderPresent(){
	SDL_RenderPresent(renderer);
}

int Renderer::colour(int r, int g, int b) {
	return 0;
}
