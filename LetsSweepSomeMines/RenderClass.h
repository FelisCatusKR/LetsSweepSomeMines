#ifndef RENDERCLASS_H
#define RENDERCLASS_H

#include <cstdio>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"

constexpr int CELL_SIZE = 32;
constexpr int MENUSCREEN_WIDTH = 416;
constexpr int MENUSCREEN_HEIGHT = 544;
constexpr int MENUBUTTON_WIDTH = 192;
constexpr int MENUBUTTON_HEIGHT = 128;
constexpr int MENUBUTTON_MARGIN_X = 112;
constexpr int MENUBUTTON_MARGIN_Y = 40;
constexpr int GAME_HEADER_HEIGHT = 64;

enum CellStatus {
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
  Main_Hard_Pressed
};

class RenderClass {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Texture* cellTexture[20];

  struct RectUnit {
    SDL_Rect r;
    enum CellStatus status;
  };
  std::vector<RectUnit> rect;

  struct TimerUnit {
    char str[1000];
    SDL_Texture* texture;
    SDL_Rect r;
  };
  TimerUnit timerUnit;

  int width;
  int height;
  int windowWidth;
  int windowHeight;
  bool isInGame;

  const char* fontFile = "RobotoMono-Regular.ttf";
  const int fontSize = 16;

 public:
  ~RenderClass();
  SDL_Texture* SurfaceToTexture(SDL_Surface* surface);
  bool Init();
  void LoadBMPs();
  void DrawCell(int index, enum CellStatus cellStatus);
  void DrawTimer(double timer);
  void ResizeWindow();
  void MainMenu();
  void NewGame(int w, int h);
  void Render();
};

#endif  // !RENDERCLASS_H
