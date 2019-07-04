#include "Init.h"
#include "Game.h"

SDL_Window* window;
SDL_Renderer* renderer;

int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

SDL_Rect playerPos = {
  20, //x
  20, //y
  20, //w
  20  //h
};

int main(int argc, char* argv[]) {
  if (Init() == false)
    return -1;

  RunGame();

	return 0;
}
