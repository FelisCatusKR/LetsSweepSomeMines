#ifndef GAME_H
#define GAME_H

#include "SDL.h"

extern SDL_Renderer* renderer;
extern SDL_Rect playerPos;

void Render();
void RunGame();

#endif // !GAME_H
