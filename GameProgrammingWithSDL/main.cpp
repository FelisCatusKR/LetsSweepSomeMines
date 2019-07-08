#include "Game.h"
#include "Init.h"
#include "MineField.h"


SDL_Window* window;
SDL_Renderer* renderer;
MineField* minefield;
SDL_Surface* surfaceArr[13];

int posX = 100;
int posY = 200;
int cellX = 11;
int cellY = 13;
int mineNum = 20;
int sizeX = cellX * CELL_SIZE;
int sizeY = cellY * CELL_SIZE;

int main(int argc, char* argv[]) {
  if (Init() == false) return -1;
  Run();

  return 0;
}
