#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "RenderClass.h"
#include "MineField.h"

class GameEngine {
private:
  RenderClass* renderClass;
  MineField* mineField;
  int width = DEFAULT_MINEFIELD_WIDTH;
  int height = DEFAULT_MINEFIELD_HEIGHT;
  int totalMines = DEFAULT_MINEFIELD_TOTALMINES;
  bool minePlaced = false;
  bool gameFinished = false;
  int foundMines = 0;
  Point posMineExploded = { -1, -1 };
public:
  GameEngine();
  bool Init();
  void RunGame();
  void LeftButtonAction(Point pos);
  void RightButtonAction(Point pos);
  enum CellStatus GetCellStatus(Point pos);
};

#endif  // !GAME_ENGINE_H
