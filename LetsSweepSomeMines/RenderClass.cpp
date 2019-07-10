#include "RenderClass.h"

bool RenderClass::Init() {
  if (InitSDL() == false) return false;
  return true;
}

RenderClass::~RenderClass() {
  for (int i = 0; i < 20; i++) SDL_DestroyTexture(cellTexture[i]);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool RenderClass::InitSDL() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void RenderClass::LoadBMPs() {
  cellTexture[Cell_Pressed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_Pressed.bmp"));
  cellTexture[Cell_1] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_1.bmp"));
  cellTexture[Cell_2] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_2.bmp"));
  cellTexture[Cell_3] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_3.bmp"));
  cellTexture[Cell_4] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_4.bmp"));
  cellTexture[Cell_5] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_5.bmp"));
  cellTexture[Cell_6] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_6.bmp"));
  cellTexture[Cell_7] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_7.bmp"));
  cellTexture[Cell_8] =
      SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Images/Mine_8.bmp"));
  cellTexture[Cell_MineExposed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_MineExposed.bmp"));
  cellTexture[Cell_Pressing] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_Pressing.bmp"));
  cellTexture[Cell_NotPressed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_NotPressed.bmp"));
  cellTexture[Cell_FlagPlaced] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_FlagPlaced.bmp"));
  cellTexture[Cell_MineExploded] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Mine_MineExploded.bmp"));
  cellTexture[Main_Easy] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Easy.bmp"));
  cellTexture[Main_Easy_Pressed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Easy_Pressed.bmp"));
  cellTexture[Main_Normal] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Normal.bmp"));
  cellTexture[Main_Normal_Pressed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Normal_Pressed.bmp"));
  cellTexture[Main_Hard] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Hard.bmp"));
  cellTexture[Main_Hard_Pressed] = SDL_CreateTextureFromSurface(
      renderer, SDL_LoadBMP("Images/Main_Hard_Pressed.bmp"));
}

bool RenderClass::ResizeWindow() {
  if (window != NULL && SDL_GetRenderer(window) != NULL)
    SDL_DestroyRenderer(renderer);

  if (window == NULL) {
    window = SDL_CreateWindow("LetsSweepSomeMine", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, windowWidth,
                              windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      std::cout << " Failed to create window : " << SDL_GetError() << std::endl;
      return false;
    }
  } else
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

  LoadBMPs();

  return true;
}

void RenderClass::DrawCell(int index, enum CellStatus cellStatus) {
  SDL_RenderCopy(renderer, cellTexture[cellStatus], nullptr, &rect[index]);
}

bool RenderClass::MainMenu() {
  windowWidth = 13 * CELL_SIZE;
  windowHeight = 15 * CELL_SIZE;
  if (ResizeWindow() == false) return false;

  for (auto i : rect) SDL_RectEmpty(&i);
  rect.clear();
  rect.resize(3);
  for (int i = 0; i < 3; i++) {
    rect[i].w = MENUBUTTON_WIDTH;
    rect[i].h = MENUBUTTON_HEIGHT;
    rect[i].x = BUTTON_SPACE_X;
    rect[i].y = BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * i;
  }

  return true;
}

bool RenderClass::NewGame(int w, int h) {
  width = w;
  height = h;
  windowWidth = w * CELL_SIZE;
  windowHeight = h * CELL_SIZE;

  if (ResizeWindow() == false) return false;

  rect.clear();
  rect.resize(width * height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      rect[i + j * width].x = i * CELL_SIZE;
      rect[i + j * width].y = j * CELL_SIZE;
      rect[i + j * width].w = CELL_SIZE;
      rect[i + j * width].h = CELL_SIZE;
    }
  }

  return true;
}

void RenderClass::Render() { SDL_RenderPresent(renderer); }