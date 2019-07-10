#ifndef RENDERCLASS_H
#define RENDERCLASS_H

#include <iostream>
#include <vector>
#include "SDL.H"

constexpr int CELL_SIZE = 32;
constexpr int MENUSCREEN_WIDTH = 416;
constexpr int MENUSCREEN_HEIGHT = 544;
constexpr int MENUBUTTON_WIDTH = 192;
constexpr int MENUBUTTON_HEIGHT = 128;
constexpr int MENUBUTTON_MARGIN_X = 112;
constexpr int MENUBUTTON_MARGIN_Y = 40;

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
  struct RectUnit {
    SDL_Rect r;
    enum CellStatus status;
  };
  std::vector<RectUnit> rect;
  int width;
  int height;
  int windowWidth = MENUSCREEN_WIDTH;
  int windowHeight = MENUSCREEN_HEIGHT;

 public:
  ~RenderClass();
  bool Init();
  void LoadBMPs();
  void DrawCell(int index, enum CellStatus cellStatus);
  void ResizeWindow();
  void MainMenu();
  void NewGame(int w, int h);
  void Render();
};

#endif  // !RENDERCLASS_H
