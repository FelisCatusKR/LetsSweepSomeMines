#include "MineField.h"

MineField::MineField(int w, int h, int mineNum) {
  width = w;
  height = h;
  totalCells = width * height;
  totalMines = mineNum;
  cell.resize(static_cast<size_t>(totalCells));
}

void MineField::PlaceMines(Point firstClickPos) {
  std::random_device generator;
  std::uniform_int_distribution<int> dist(0, width * height - 1);

  int curPlacedMine = 0;
  while (curPlacedMine < totalMines) {
    int rng = dist(generator);
    int x = rng % width;
    int y = rng / width;

    if (x == firstClickPos.x && y == firstClickPos.y) continue;
    if (cell[rng].isMine) continue;
    cell[rng].isMine = true;
    curPlacedMine++;

    for (int i = 0; i < 8; i++) {
      Point newPos = {x + dx_8[i], y + dy_8[i]};
      if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 ||
          newPos.y >= height)
        continue;
      int posIndex = CalcIndex(newPos);
      cell[posIndex].nearMine++;
    }
  }

  minePlaced = true;
}

void MineField::ChangePressStatus(Point pos) {
  int posIndex = CalcIndex(pos);
  cell[posIndex].isPressed = true;
  if (cell[posIndex].isFlagPlaced) ChangeFlagStatus(pos);
  openedCells++;

  if (!minePlaced) PlaceMines(pos);

  if (cell[posIndex].nearMine == 0) {
    std::queue<Point> q;
    q.push(pos);
    while (!q.empty()) {
      int x = q.front().x;
      int y = q.front().y;
      q.pop();
      for (int i = 0; i < 8; i++) {
        Point newPos = {x + dx_8[i], y + dy_8[i]};
        if (newPos.x < 0 || newPos.x >= width ||
            newPos.y < 0 || newPos.y >= height)
          continue;
        int newPosIndex = CalcIndex(newPos);
        if (cell[newPosIndex].isPressed) continue;
        if (cell[newPosIndex].isFlagPlaced) continue;
        cell[newPosIndex].isPressed = true;
        if (cell[newPosIndex].isFlagPlaced) ChangeFlagStatus(newPos);
        openedCells++;
        if (cell[newPosIndex].nearMine != 0) continue;
        q.push({newPos});
      }
    }
  }
}

void MineField::ChangeFlagStatus(Point pos) {
  int posIndex = CalcIndex(pos);
  // If a player used all flags and tried to place a flag, do nothing
  if (flagPlaceCount == totalMines && !cell[posIndex].isFlagPlaced) return;

  cell[posIndex].isFlagPlaced = !cell[posIndex].isFlagPlaced;
  if (cell[posIndex].isMine) {
    if (cell[posIndex].isFlagPlaced)
      foundMines++;
    else
      foundMines--;
  }
  if (cell[posIndex].isFlagPlaced)
    flagPlaceCount++;
  else
    flagPlaceCount--;
}