#ifndef INIT_H
#define INIT_H

#include "SDL.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int posX, posY, sizeX, sizeY;

bool Init();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void InitRenderer();

#endif // !INIT_H
