#include "MineField.h"
#include <iostream>
#include <random>

MineField::MineField(std::pair<int, int> coor, int mine) {
  std::cout << "MineField Created" << std::endl;
  width = coor.first;
  height = coor.second;
  totalMine = mine;
  cell = new Cell*[width];
  for (int i = 0; i < width; i++) cell[i] = new Cell[height];
}

MineField::~MineField() { std::cout << "MineField Destructed" << std::endl; }

void MineField::PlaceMines(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  std::random_device generator;
  std::uniform_int_distribution<int> dist(0, width * height - 1);

  int curPlacedMine = 0;
  while (curPlacedMine < totalMine) {
    int rng = dist(generator);
    int x = rng % width;
    int y = rng / width;

    if (x == posX && y == posY) continue;
    if (cell[x][y].isMine) continue;

    cell[x][y].isMine = true;
    curPlacedMine++;

    for (int i = 0; i < 8; i++) {
      int newX = x + dx_8[i];
      int newY = y + dy_8[i];
      if (newX < 0 || newX >= width || newY < 0 || newY >= height) continue;
      cell[newX][newY].nearMine++;
    }
  }

  minePlaced = true;
}

void MineField::LeftButtonAction(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  cell[posX][posY].clickStatus = 2;

  if (cell[posX][posY].isMine) {
    explodedPos = {posX, posY};
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        cell[i][j].clickStatus = 2;
      }
    }
    ChangeGameStatus();
  } else {
    if (!minePlaced) PlaceMines({posX, posY});
    if (cell[posX][posY].nearMine == 0) {
      std::queue<std::pair<int, int>> q;
      q.push({posX, posY});
      while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++) {
          int newX = x + dx_8[i];
          int newY = y + dy_8[i];
          if (newX < 0 || newX >= width || newY < 0 || newY >= height) continue;
          if (cell[newX][newY].clickStatus == 2) continue;
          if (cell[newX][newY].isMine) continue;
          cell[newX][newY].clickStatus = 2;
          if (cell[newX][newY].nearMine != 0) continue;
          q.push({newX, newY});
        }
      }
    }
  }
}

void MineField::RightButtonAction(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  if (!cell[posX][posY].isFlagPlaced) {
    cell[posX][posY].isFlagPlaced = true;
    if (cell[posX][posY].isMine) foundMine++;
  } else {
    cell[posX][posY].isFlagPlaced = false;
    if (cell[posX][posY].isMine) foundMine--;
  }
}

void MineField::ChangeCellClickStatus(std::pair<int, int> coor, int st) {
  int posX = coor.first;
  int posY = coor.second;

  cell[posX][posY].clickStatus = st;
}

void MineField::ChangeGameStatus() { isFinished = true; }

int MineField::GetClickStatus(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  return cell[posX][posY].clickStatus;
}

bool MineField::GetFlagStatus(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  return cell[posX][posY].isFlagPlaced;
}
bool MineField::GetMineStatus(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  return cell[posX][posY].isMine;
}

int MineField::GetNearMine(std::pair<int, int> coor) {
  int posX = coor.first;
  int posY = coor.second;

  return cell[posX][posY].nearMine;
}

bool MineField::GetGameStatus() { return isFinished; }

std::pair<int, int> MineField::GetExplodedPos() { return explodedPos; }