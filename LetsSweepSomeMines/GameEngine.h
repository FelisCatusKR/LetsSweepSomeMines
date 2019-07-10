#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "MineField.h"
#include "RenderClass.h"

class GameEngine {
 private:
  struct DiffStruct {
    int w, h, totalM;
  };
  DiffStruct diffStruct[3] = {{11, 13, 15}, {13, 17, 30}, {23, 19, 60}};
  enum Difficulty { Easy = 0, Normal, Hard };
  enum Difficulty diff;
  RenderClass* renderClass;
  MineField* mineField;
  bool gameFinished = false;
  int foundMines = 0;

 public:
  ~GameEngine() { delete renderClass; }
  bool Init();
  bool GameLoop();
  bool MainMenu();
  void RunGame();
  void LeftButtonAction(Point pos);
  void RightButtonAction(Point pos);
  enum CellStatus GetCellStatus(Point pos);
};

#endif  // !GAME_ENGINE_H
