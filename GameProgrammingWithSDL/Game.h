#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "MineField.h"
#define CELL_SIZE 32

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern MineField* minefield;
extern SDL_Surface* surfaceArr[13];

extern int cellX, cellY, mineNum;
extern int sizeX, sizeY;


void Run();
void ConfigureRenderer();
void LoadBMPs();
void Render();
void RunGame();

#endif  // !GAME_H
