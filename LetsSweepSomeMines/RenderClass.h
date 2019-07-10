#ifndef RENDERCLASS_H
#define RENDERCLASS_H

#include <iostream>
#include <vector>
#include "SDL.H"

constexpr int CELL_SIZE = 32;
constexpr int MENUBUTTON_WIDTH = 192;
constexpr int MENUBUTTON_HEIGHT = 128;
constexpr int BUTTON_SPACE_X = 112;
constexpr int BUTTON_SPACE_Y = 24;

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
  SDL_Texture* cellTexture[20];
  std::vector<SDL_Rect> rect;
  int width;
  int height;
  int windowWidth;
  int windowHeight;

 public:
  ~RenderClass();
  bool Init();
  bool InitSDL();
  void LoadBMPs();
  void DrawCell(int index, enum CellStatus cellStatus);
  bool ResizeWindow();
  bool MainMenu();
  bool NewGame(int w, int h);
  void Render();
};

#endif  // !RENDERCLASS_H
