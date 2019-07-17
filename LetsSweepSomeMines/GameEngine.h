#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <chrono>
#include "MineField.h"
#include "RenderClass.h"

class GameEngine {
 private:
  struct DiffStruct {
    int w, h, totalM;
  };
  DiffStruct diffStruct[3] = {{11, 13, 15}, {13, 17, 35}, {23, 19, 75}};
  enum class Difficulty { Easy = 0, Normal, Hard };
  Difficulty diff;
  enum class GameStatus { NotFinished = 0, Win, Lose };
  GameStatus gameStatus;
  enum class ClickedPos { Cell = 0, Button, Background };
  class Timer {
   private:
    bool isInit = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> timePrev;

   public:
    void Init() {
      isInit = true;
      timePrev = std::chrono::high_resolution_clock::now();
    }
    bool GetInit() { return isInit; }
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
  int foundMines;

 public:
  ~GameEngine() { delete renderClass; }
  bool Init();
  void GameLoop();
  bool MainMenu();
  bool RunGame();
  void LeftButtonAction(Point pos);
  void RightButtonAction(Point pos);
  ButtonStatus GetCellStatus(Point pos);
  ClickedPos CheckClickedPos(SDL_Event event);
};

#endif  // !GAME_ENGINE_H
