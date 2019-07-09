#include "Init.h"
#include <iostream>

bool Init() {
  if (InitSDL() == false) return false;

  if (CreateWindow() == false) return false;

  if (CreateRenderer() == false) return false;

  return true;
}

bool InitSDL() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool CreateWindow() {
  window =
      SDL_CreateWindow("SDL Test", posX, posY, sizeX, sizeY, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    std::cout << " Failed to create window : " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool CreateRenderer() {
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL) {
    std::cout << " Failed to create renderer : " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}