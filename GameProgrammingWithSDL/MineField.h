#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <utility>
#include <vector>
#include <queue>
#include "SDL.h"

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

const int dx_8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int dy_8[8] = {1, 1, 1, 0, -1, -1, -1, 0};

class MineField {
 private:
  struct Cell {
    // A bool variable which saves its mine plant status
    bool isMine = false;
    // 0 for unclicked, 1 for clicking, 2 for clicked
    int clickStatus = 0;
    // A bool variable which saves whether field has a flag
    bool isFlagPlaced = false;
    // A integer variavle which saves numbers of mines nearby
    int nearMine = 0;
  };
  // A 2-D Cell class vector of the MineField
  Cell** cell;
  bool isFinished = false;
  bool minePlaced = false;
  int width = 0;
  int height = 0;
  int totalMine = 0;
  int foundMine = 0;

 public:
  // Initiate the MineField without mines
  MineField(std::pair<int, int>, int);

  // Destruct the MineField
  ~MineField();

  // Place mines at the MineField
  void PlaceMines(std::pair<int, int>);

  void ChangeCellClickStatus(std::pair<int, int>, int);
  void LeftButtonAction(std::pair<int, int>);
  void RightButtonAction(std::pair<int, int>);
  void ChangeGameStatus();

  // Returns the click status of clicked cell
  // 0 for unclicked, 1 for clicking, 2 for clicked
  int GetClickStatus(std::pair<int, int>);

  bool GetFlagStatus(std::pair<int, int>);
  bool GetMineStatus(std::pair<int, int>);
  int GetNearMine(std::pair<int, int>);
  bool GetGameStatus();
};

#endif  // !MINEFIELD_H
