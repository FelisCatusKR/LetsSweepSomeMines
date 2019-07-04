#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return -1;
	}

  int posX = 100;
  int posY = 200;
  int sizeX = 300;
  int sizeY = 400;

  SDL_Window* window;
  window = SDL_CreateWindow("SDL Test", posX, posY, sizeX, sizeY, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << " Failed to create window : " << SDL_GetError() << std::endl;
    return -1;
  }

  SDL_Renderer* renderer;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cout << " Failed to create renderer : " << SDL_GetError() << std::endl;
    return -1;
  }

  SDL_RenderSetLogicalSize(renderer, sizeX, sizeY);
  SDL_SetRenderDrawColor(renderer, 128, 128, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_Delay(3000);
  SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}