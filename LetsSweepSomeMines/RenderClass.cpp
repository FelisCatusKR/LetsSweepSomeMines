#include "RenderClass.h"

bool RenderClass::Init() {
  windowWidth = MENUSCREEN_WIDTH;
  windowHeight = MENUSCREEN_HEIGHT;

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("LetsSweepSomeMine", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
                            SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << " Failed to create a window : " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == nullptr) {
    std::cout << " Failed to create a renderer : " << SDL_GetError()
              << std::endl;
    return false;
  }

  if (TTF_Init() == -1) {
    std::cout << " Failed to initialize SDL_ttf : " << SDL_GetError()
              << std::endl;
    return false;
  }

  font = TTF_OpenFont(fontFile, fontSize);
  if (font == nullptr) {
    std::cout << " Failed to load a font file : " << SDL_GetError()
              << std::endl;
    return false;
  }

  LoadBMPs();
  return true;
}

RenderClass::~RenderClass() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  SDL_Quit();
}

SDL_Texture* RenderClass::SurfaceToTexture(SDL_Surface* surface) {
  SDL_Texture* texture;
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

void RenderClass::LoadBMPs() {
  cellTexture[Cell_Pressed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_Pressed.bmp"));
  cellTexture[Cell_1] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_1.bmp"));
  cellTexture[Cell_2] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_2.bmp"));
  cellTexture[Cell_3] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_3.bmp"));
  cellTexture[Cell_4] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_4.bmp"));
  cellTexture[Cell_5] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_5.bmp"));
  cellTexture[Cell_6] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_6.bmp"));
  cellTexture[Cell_7] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_7.bmp"));
  cellTexture[Cell_8] = SurfaceToTexture(SDL_LoadBMP("Images/Mine_8.bmp"));
  cellTexture[Cell_MineExposed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_MineExposed.bmp"));
  cellTexture[Cell_Pressing] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_Pressing.bmp"));
  cellTexture[Cell_NotPressed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_NotPressed.bmp"));
  cellTexture[Cell_FlagPlaced] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_FlagPlaced.bmp"));
  cellTexture[Cell_MineExploded] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_MineExploded.bmp"));
  cellTexture[Main_Easy] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Easy.bmp"));
  cellTexture[Main_Easy_Pressed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Easy_Pressed.bmp"));
  cellTexture[Main_Normal] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Normal.bmp"));
  cellTexture[Main_Normal_Pressed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Normal_Pressed.bmp"));
  cellTexture[Main_Hard] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Hard.bmp"));
  cellTexture[Main_Hard_Pressed] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Hard_Pressed.bmp"));
}

void RenderClass::ResizeWindow() {
  // Set the size of a renderer to the same as window
  SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

  // Set the color of a renderer to grey
  SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
  SDL_RenderClear(renderer);

  // Set the size of a window
  SDL_SetWindowSize(window, windowWidth, windowHeight);
}

void RenderClass::DrawCell(int index, enum CellStatus cellStatus) {
  rect[index].status = cellStatus;
}

void RenderClass::DrawTimer(double timer) {
  std::sprintf(timerUnit.str, "%.1lf", timer);
}

void RenderClass::DrawRemainCount(int count)
{
  std::sprintf(remainCountUnit.str, "%03d", count);
}

void RenderClass::MainMenu() {
  windowWidth = MENUSCREEN_WIDTH;
  windowHeight = MENUSCREEN_HEIGHT;
  ResizeWindow();
  isInGame = false;

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
  windowHeight = h * CELL_SIZE + GAME_HEADER_HEIGHT;
  ResizeWindow();
  timerUnit.r.x = windowWidth - 64;
  timerUnit.r.y = 12;
  remainCountUnit.r.x = 12;
  remainCountUnit.r.y = 12;
  isInGame = true;

  rect.clear();
  rect.resize(width * height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      rect[i + j * width].r.x = i * CELL_SIZE;
      rect[i + j * width].r.y = j * CELL_SIZE + GAME_HEADER_HEIGHT;
      rect[i + j * width].r.w = CELL_SIZE;
      rect[i + j * width].r.h = CELL_SIZE;
    }
  }
}

void RenderClass::Render() {
  // Clear a renderer
  SDL_RenderClear(renderer);

  // Draw buttons in a rect vector
  for (auto i : rect)
    SDL_RenderCopy(renderer, cellTexture[i.status], nullptr, &(i.r));

  // Draw a timer if it is a game screeen
  if (isInGame) {
    SDL_Surface* timerSurface =
        TTF_RenderText_Solid(font, timerUnit.str, {192, 0, 0, 255});
    timerUnit.texture = SurfaceToTexture(timerSurface);
    SDL_QueryTexture(timerUnit.texture, nullptr, nullptr, &timerUnit.r.w,
                     &timerUnit.r.h);
    SDL_RenderCopy(renderer, timerUnit.texture, nullptr, &timerUnit.r);

    SDL_Surface* remainCountSurface =
      TTF_RenderText_Solid(font, remainCountUnit.str, {192, 0, 0, 255});
    remainCountUnit.texture = SurfaceToTexture(remainCountSurface);
    SDL_QueryTexture(remainCountUnit.texture, nullptr, nullptr, &remainCountUnit.r.w,
      &remainCountUnit.r.h);
    SDL_RenderCopy(renderer, remainCountUnit.texture, nullptr, &remainCountUnit.r);

  }

  SDL_RenderPresent(renderer);
}