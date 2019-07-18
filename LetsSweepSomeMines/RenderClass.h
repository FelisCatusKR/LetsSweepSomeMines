#ifndef RENDERCLASS_H
#define RENDERCLASS_H

#include <cstdio>
#include <iostream>
#include <vector>
#include "SDL.h"

constexpr int CELL_SIZE = 32;
constexpr int MENUSCREEN_WIDTH = 416;
constexpr int MENUSCREEN_HEIGHT = 544;
constexpr int MENUBUTTON_WIDTH = 192;
constexpr int MENUBUTTON_HEIGHT = 128;
constexpr int MENUBUTTON_MARGIN_X = 112;
constexpr int MENUBUTTON_MARGIN_Y = 40;
constexpr int GAME_HEADER_HEIGHT = 72;
constexpr int RESTARTBUTTON_WIDTH = 64;
constexpr int RESTARTBUTTON_HEIGHT = 64;
constexpr int RESTARTBUTTON_PADDING =
    (GAME_HEADER_HEIGHT - RESTARTBUTTON_HEIGHT) / 2;
constexpr int DIGIT_WIDTH = 24;
constexpr int DIGIT_HEIGHT = 48;
constexpr int DIGIT_PADDING = 12;

enum class ButtonStatus {
  Cell_Pressed = 0,
  Cell_1,
  Cell_2,
  Cell_3,
  Cell_4,
  Cell_5,
  Cell_6,
  Cell_7,
  Cell_8,
  Cell_MineExposed,
  Cell_Pressing,
  Cell_NotPressed,
  Cell_FlagPlaced,
  Cell_MineExploded,
  Main_Easy,
  Main_Easy_Pressed,
  Main_Normal,
  Main_Normal_Pressed,
  Main_Hard,
  Main_Hard_Pressed,
  Restart_NotPressed,
  Restart_Pressing,
  Restart_Win,
  Restart_Lose,
  Restart_Clicking
};

enum class DigitStatus {
  Digit_0 = 0,
  Digit_1,
  Digit_2,
  Digit_3,
  Digit_4,
  Digit_5,
  Digit_6,
  Digit_7,
  Digit_8,
  Digit_9,
  Digit_Off
};

class RenderClass {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* buttonTexture[25];
  SDL_Texture* digitTexture[21];

  struct ButtonUnit {
    SDL_Rect r;
    ButtonStatus status;
  };
  std::vector<ButtonUnit> buttonArray;

  struct DigitUnit {
    SDL_Rect r;
    DigitStatus status = DigitStatus::Digit_Off;
  };
  std::vector<DigitUnit> remainFlagArray;
  std::vector<DigitUnit> timerArray;

  int width;
  int height;
  int windowWidth;
  int windowHeight;
  bool isInGame;

 public:
  ~RenderClass();
  SDL_Texture* SurfaceToTexture(SDL_Surface* surface);
  bool Init();
  void LoadBMPs();
  void DrawCell(int index, ButtonStatus cellStatus);
  void DrawTimer(int timer);
  void DrawRemainCount(int count);
  void ResizeWindow();
  void MainMenu();
  void NewGame(int w, int h);
  void Render();
};

#endif  // !RENDERCLASS_H
