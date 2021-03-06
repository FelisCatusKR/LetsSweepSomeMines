#include "GameEngine.h"

int main(int argc, char* argv[]) {
  GameEngine* gameEngine = new GameEngine;

  if (gameEngine->Init() == false) return -1;
  gameEngine->GameLoop();

  delete gameEngine;

  return 0;
}
