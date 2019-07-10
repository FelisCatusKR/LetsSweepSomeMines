#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <queue>
#include <random>
#include <vector>

constexpr int DEFAULT_MINEFIELD_WIDTH = 13;
constexpr int DEFAULT_MINEFIELD_HEIGHT = 15;
constexpr int DEFAULT_MINEFIELD_TOTALMINES = 20;

constexpr int dx[4] = {0, 0, 1, -1};
constexpr int dy[4] = {1, -1, 0, 0};

constexpr int dx_8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
constexpr int dy_8[8] = {1, 1, 1, 0, -1, -1, -1, 0};

struct Point {
  int x, y;
};

class MineField {
 private:
  struct Cell {
    // A bool variable which saves its mine plant status
    bool isMine = false;
    // A bool variable which saves its click status
    bool isPressed = false;
    // A bool variable which saves whether field has a flag
    bool isFlagPlaced = false;
    // A integer variavle which saves numbers of mines nearby
    int nearMine = 0;
  };

  // A 2-D Cell class vector of the MineField
  std::vector<Cell> cell;
  bool minePlaced = false;
  int width = 0;
  int height = 0;
  int totalMines = 0;
  Point posMineExploded = {-1, -1};

 public:
  // Initiate the MineField without mines
  MineField(int w, int h, int mineNum);

  // Place mines at the MineField
  void PlaceMines(Point firstClickedPos);

  // Inverts the press status of selected cell
  void ChangePressStatus(Point pos);

  // Inverts the flag status of selected cell
  void ChangeFlagStatus(Point pos);

  void ChangeMineExploded(Point pos) { posMineExploded = pos; }
  Point GetMineExploded() { return posMineExploded; }

  bool GetMinePlaced() { return minePlaced; }
  // Returns the press status of cell
  bool GetPressStatus(Point pos) { return cell[CalcIndex(pos)].isPressed; }

  // Returns the flag status of cell
  bool GetFlagStatus(Point pos) { return cell[CalcIndex(pos)].isFlagPlaced; }

  // Returns the mine status of cell
  bool GetMineStatus(Point pos) { return cell[CalcIndex(pos)].isMine; }

  // Returns the number of mines nearby selected cell
  int GetNearMine(Point pos) { return cell[CalcIndex(pos)].nearMine; }

  int CalcIndex(Point pos) { return pos.x + pos.y * width; }
};

#endif  // !MINEFIELD_H
