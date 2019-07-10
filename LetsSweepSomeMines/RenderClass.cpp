#include "RenderClass.h"

bool RenderClass::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("LetsSweepSomeMine", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << " Failed to create window : " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == NULL) {
    std::cout << " Failed to create renderer : " << SDL_GetError() << std::endl;
    return false;
  }

  LoadBMPs();
  return true;
}

RenderClass::~RenderClass() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
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

void RenderClass::ResizeWindow() {
  // Set the size of a window
  SDL_SetWindowSize(window, windowWidth, windowHeight);

  // Set the size of a renderer to the same as window
  SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
}

void RenderClass::DrawCell(int index, enum CellStatus cellStatus) {
  rect[index].status = cellStatus;
}

void RenderClass::MainMenu() {
  windowWidth = MENUSCREEN_WIDTH;
  windowHeight = MENUSCREEN_HEIGHT;
  ResizeWindow();

  for (auto i : rect) SDL_RectEmpty(&(i.r));
  rect.clear();
  rect.resize(3);
  for (int i = 0; i < 3; i++) {
    rect[i].r.w = MENUBUTTON_WIDTH;
    rect[i].r.h = MENUBUTTON_HEIGHT;
    rect[i].r.x = MENUBUTTON_MARGIN_X;
    rect[i].r.y = MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * i;
  }
}

void RenderClass::NewGame(int w, int h) {
  width = w;
  height = h;
  windowWidth = w * CELL_SIZE;
  windowHeight = h * CELL_SIZE;
  ResizeWindow();

  rect.clear();
  rect.resize(width * height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      rect[i + j * width].r.x = i * CELL_SIZE;
      rect[i + j * width].r.y = j * CELL_SIZE;
      rect[i + j * width].r.w = CELL_SIZE;
      rect[i + j * width].r.h = CELL_SIZE;
    }
  }
}

void RenderClass::Render() {
  // Set the color of renderer to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (auto i : rect)
    SDL_RenderCopy(renderer, cellTexture[i.status], nullptr, &(i.r));

  SDL_RenderPresent(renderer);
}