#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "MineField.h"
#include "RenderClass.h"
#include <chrono>

class GameEngine {
 private:
  struct DiffStruct {
    int w, h, totalM;
  };
  DiffStruct diffStruct[3] = {{11, 13, 15}, {13, 17, 35}, {23, 19, 75}};
  enum Difficulty { Easy = 0, Normal, Hard };
  Difficulty diff;

  class Timer {
   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> timePrev;
   public:
    void Init() { timePrev = std::chrono::high_resolution_clock::now(); }
    double GetDelta() {
      std::chrono::time_point<std::chrono::high_resolution_clock> timeCurrent;
      if (timeCurrent.time_since_epoch() == timePrev.time_since_epoch())
        return 0.0;
      timeCurrent = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> delta(timeCurrent - timePrev);
      return delta.count();
    }
  };
  Timer* timer;
  double curTime;
  RenderClass* renderClass;
  MineField* mineField;
  bool gameFinished = false;
  int foundMines = 0;

 public:
  ~GameEngine() { delete renderClass; }
  bool Init();
  void GameLoop();
  bool MainMenu();
  void RunGame();
  void LeftButtonAction(Point pos);
  void RightButtonAction(Point pos);
  enum CellStatus GetCellStatus(Point pos);
};

#endif  // !GAME_ENGINE_H
