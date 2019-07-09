#include "RenderClass.h"

RenderClass::RenderClass(int w, int h) {
  width = w;
  height = h;
  windowWidth = width * CELL_SIZE;
  windowHeight = height * CELL_SIZE;
}

bool RenderClass::Init() {
  if (InitSDL() == false)
    return false;

  if (ConfigureRenderer() == false)
    return false;

  LoadBMPs();
  return true;
}

void RenderClass::LoadBMPs() {
  cellTexture[Cell_Pressed] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_Pressed.bmp"));
  cellTexture[Cell_1] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_1.bmp"));
  cellTexture[Cell_2] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_2.bmp"));
  cellTexture[Cell_3] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_3.bmp"));
  cellTexture[Cell_4] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_4.bmp"));
  cellTexture[Cell_5] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_5.bmp"));
  cellTexture[Cell_6] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_6.bmp"));
  cellTexture[Cell_7] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_7.bmp"));
  cellTexture[Cell_8] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_8.bmp"));
  cellTexture[Cell_MineExposed] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_MineExposed.bmp"));
  cellTexture[Cell_Pressing] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_Pressing.bmp"));
  cellTexture[Cell_NotPressed] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_NotPressed.bmp"));
  cellTexture[Cell_FlagPlaced] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_FlagPlaced.bmp"));
  cellTexture[Cell_MineExploded] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_MineExploded.bmp"));
}

bool RenderClass::InitSDL() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

bool RenderClass::ConfigureRenderer() {
  if (window != NULL && SDL_GetRenderer(window) != NULL)
    SDL_DestroyRenderer(renderer);

  if (window == NULL) {
    window = SDL_CreateWindow("LetsSweepSomeMine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cout << " Failed to create window : " << SDL_GetError() << std::endl;
      return false;
    }
  }
  else
    SDL_SetWindowSize(window, windowWidth, windowHeight);

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL) {
    std::cout << " Failed to create renderer : " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_SetWindowSize(window, windowWidth, windowHeight);

  // Set size of renderer to the same as window
  SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

  // Set color of renderer to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_RenderClear(renderer);

  rect.clear();
  rect.resize(width * height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      rect[i + j * width].x = i * CELL_SIZE;
      rect[i + j * width].y = j * CELL_SIZE;
      rect[i + j * width].w = CELL_SIZE;
      rect[i + j * width].h = CELL_SIZE;
      DrawCell(i, j, Cell_NotPressed);
    }
  }

  return true;
}

void RenderClass::DrawCell(int x, int y, enum CellStatus cellStatus) {
  SDL_RenderCopy(renderer, cellTexture[cellStatus], nullptr, &rect[x + y * width]);
}

bool RenderClass::ResizeWindow(int w, int h) {
  windowWidth = w;
  windowHeight = h;

  if (ConfigureRenderer() == false)
    return false;
  else
    return true;
}

void RenderClass::Render() {
  SDL_RenderPresent(renderer);
}