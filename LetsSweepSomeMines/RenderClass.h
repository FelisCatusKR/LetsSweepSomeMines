#ifndef RENDERCLASS_H
#define RENDERCLASS_H

#include "SDL.H"
#include <iostream>
#include <vector>

constexpr int CELL_SIZE = 32;

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
  Cell_MineExploded
};

class RenderClass {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* cellTexture[14];
  std::vector<SDL_Rect> rect;
  int width;
  int height;
  int windowWidth;
  int windowHeight;
public:
  RenderClass(int w, int h);
  bool Init();
  bool InitSDL();
  bool ConfigureRenderer();
  void LoadBMPs();
  void DrawCell(int x, int y, enum CellStatus cellStatus);
  bool ResizeWindow(int w, int h);
  void Render();
};

#endif  // !RENDERCLASS_H
