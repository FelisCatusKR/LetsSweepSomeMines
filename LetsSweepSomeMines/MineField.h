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
    // A integer variable which saves numbers of mines nearby
    int nearMine = 0;
  };

  // A 2-D Cell class vector of the MineField
  std::vector<Cell> cell;

  bool minePlaced = false;
  int width = 0;
  int height = 0;
  int totalCells = 0;
  int openedCells = 0;
  int totalMines = 0;
  int flagPlaceCount = 0;
  int foundMines = 0;
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

  Point GetMineExploded() const { return posMineExploded; }
  int GetRemainFlagCount() const { return totalMines - flagPlaceCount; }
  int GetRemainCellCount() const { return totalCells - openedCells; }
  int GetTotalMineCount() const { return totalMines; }
  int GetFoundMineCount() const { return foundMines; }
  bool GetMinePlaced() const { return minePlaced; }

  // Returns the press status of cell
  bool GetPressStatus(Point pos) const {
    return cell[CalcIndex(pos)].isPressed;
  }
  // Returns the flag status of cell
  bool GetFlagStatus(Point pos) const {
    return cell[CalcIndex(pos)].isFlagPlaced;
  }
  // Returns the mine status of cell
  bool GetMineStatus(Point pos) const { return cell[CalcIndex(pos)].isMine; }
  // Returns the number of mines nearby selected cell
  int GetNearMine(Point pos) const { return cell[CalcIndex(pos)].nearMine; }

  int CalcIndex(Point pos) const { return pos.x + pos.y * width; }
};

#endif  // !MINEFIELD_H
