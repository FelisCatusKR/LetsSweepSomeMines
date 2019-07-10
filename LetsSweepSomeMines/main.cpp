#include "GameEngine.h"

int main(int argc, char* argv[]) {
  GameEngine* gameEngine = new GameEngine;

  if (gameEngine->Init() == false) return -1;
  if (gameEngine->GameLoop() == false) return -1;

  delete gameEngine;

  return 0;
}
