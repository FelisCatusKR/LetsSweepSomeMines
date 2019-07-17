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

  LoadBMPs();

  timerArray.resize(3);
  remainFlagArray.resize(3);
  return true;
}

RenderClass::~RenderClass() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_Texture* RenderClass::SurfaceToTexture(SDL_Surface* surface) {
  SDL_Texture* texture;
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

void RenderClass::LoadBMPs() {
  buttonTexture[static_cast<int>(ButtonStatus::Cell_Pressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_Pressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_1)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_1.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_2)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_2.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_3)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_3.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_4)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_4.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_5)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_5.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_6)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_6.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_7)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_7.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_8)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_8.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_MineExposed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_MineExposed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_Pressing)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_Pressing.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_NotPressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_NotPressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_FlagPlaced)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_FlagPlaced.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Cell_MineExploded)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Mine_MineExploded.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Easy)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Easy.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Easy_Pressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Easy_Pressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Normal)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Normal.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Normal_Pressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Normal_Pressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Hard)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Hard.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Main_Hard_Pressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Main_Hard_Pressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Restart_NotPressed)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Restart_NotPressed.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Restart_Pressing)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Restart_Pressing.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Restart_Win)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Restart_Win.bmp"));
  buttonTexture[static_cast<int>(ButtonStatus::Restart_Lose)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Restart_Lose.bmp"));

  digitTexture[static_cast<int>(DigitStatus::Digit_0)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_0.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_1)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_1.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_2)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_2.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_3)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_3.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_4)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_4.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_5)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_5.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_6)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_6.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_7)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_7.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_8)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_8.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_9)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_9.bmp"));
  digitTexture[static_cast<int>(DigitStatus::Digit_Off)] =
      SurfaceToTexture(SDL_LoadBMP("Images/Display_Off.bmp"));
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

void RenderClass::DrawCell(int index, ButtonStatus cellStatus) {
  buttonArray[index].status = cellStatus;
}

void RenderClass::DrawTimer(int timer) {
  if (timer == 0) {
    timerArray[0].status = DigitStatus::Digit_0;
    return;
  }
  for (int i = 0; i < timerArray.size(); i++) {
    if (timer == 0) {
      timerArray[i].status = DigitStatus::Digit_Off;
      continue;
    }
    int tmp = timer % 10;
    timerArray[i].status = static_cast<DigitStatus>(tmp);
    timer /= 10;
  }
}

void RenderClass::DrawRemainCount(int count) {
  if (count == 0) {
    remainFlagArray[0].status = DigitStatus::Digit_0;
    return;
  }
  for (int i = 0; i < remainFlagArray.size(); i++) {
    if (count == 0) {
      remainFlagArray[i].status = DigitStatus::Digit_Off;
      continue;
    }
    int tmp = count % 10;
    remainFlagArray[i].status = static_cast<DigitStatus>(tmp);
    count /= 10;
  }
}

void RenderClass::MainMenu() {
  windowWidth = MENUSCREEN_WIDTH;
  windowHeight = MENUSCREEN_HEIGHT;
  ResizeWindow();
  isInGame = false;

  for (auto i : buttonArray) SDL_RectEmpty(&(i.r));
  buttonArray.clear();
  buttonArray.resize(3);
  for (int i = 0; i < 3; i++) {
    buttonArray[i].r.w = MENUBUTTON_WIDTH;
    buttonArray[i].r.h = MENUBUTTON_HEIGHT;
    buttonArray[i].r.x = MENUBUTTON_MARGIN_X;
    buttonArray[i].r.y = MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * i;
  }
}

void RenderClass::NewGame(int w, int h) {
  width = w;
  height = h;
  windowWidth = w * CELL_SIZE;
  windowHeight = h * CELL_SIZE + GAME_HEADER_HEIGHT;
  ResizeWindow();
  isInGame = true;

  buttonArray.clear();
  buttonArray.resize(width * height + 1);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      buttonArray[i + j * width].r.x = i * CELL_SIZE;
      buttonArray[i + j * width].r.y = j * CELL_SIZE + GAME_HEADER_HEIGHT;
      buttonArray[i + j * width].r.w = CELL_SIZE;
      buttonArray[i + j * width].r.h = CELL_SIZE;
    }
  }

  buttonArray[width * height].r.x = (windowWidth - RESTARTBUTTON_WIDTH) / 2;
  buttonArray[width * height].r.y = RESTARTBUTTON_PADDING;
  buttonArray[width * height].r.w = RESTARTBUTTON_WIDTH;
  buttonArray[width * height].r.h = RESTARTBUTTON_HEIGHT;
  buttonArray[width * height].status = ButtonStatus::Restart_NotPressed;

  for (int i = 0; i < remainFlagArray.size(); i++) {
    remainFlagArray[i].r.x =
        (static_cast<int>(remainFlagArray.size()) - 1 - i) * DIGIT_WIDTH +
        DIGIT_PADDING;
    remainFlagArray[i].r.y = DIGIT_PADDING;
    remainFlagArray[i].r.w = DIGIT_WIDTH;
    remainFlagArray[i].r.h = DIGIT_HEIGHT;
  }

  for (int i = 0; i < timerArray.size(); i++) {
    timerArray[i].r.x = windowWidth - DIGIT_WIDTH * (i + 1) - DIGIT_PADDING;
    timerArray[i].r.y = DIGIT_PADDING;
    timerArray[i].r.w = DIGIT_WIDTH;
    timerArray[i].r.h = DIGIT_HEIGHT;
  }
}

void RenderClass::Render() {
  // Clear a renderer
  SDL_RenderClear(renderer);

  // Draw objects in a buttonArray vector
  for (auto i : buttonArray)
    SDL_RenderCopy(renderer, buttonTexture[static_cast<int>(i.status)], nullptr,
                   &(i.r));

  // Draw timer and flag counter to header
  if (isInGame) {
    for (auto i : remainFlagArray)
      SDL_RenderCopy(renderer, digitTexture[static_cast<int>(i.status)],
                     nullptr, &(i.r));
    for (auto i : timerArray)
      SDL_RenderCopy(renderer, digitTexture[static_cast<int>(i.status)],
                     nullptr, &(i.r));
  }
  SDL_RenderPresent(renderer);
}