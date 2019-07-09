#include "GameEngine.h"

GameEngine::GameEngine() {
  renderClass = new RenderClass(width, height);
  mineField = new MineField(width, height, totalMines);
}

bool GameEngine::Init() {
  if (renderClass->Init() == false)
    return false;
  return true;
}

void GameEngine::RunGame() {
  bool loop = true;
  bool isClicking = false;
  Point clickPos = { -1, -1 };

  while (loop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        loop = false;
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (isClicking) continue;
          isClicking = true;
          clickPos = { event.button.x / CELL_SIZE, event.button.y / CELL_SIZE };
          if (mineField->GetPressStatus(clickPos) == true) {
            isClicking = false;
            continue;
          }
        }
        else if (event.button.button == SDL_BUTTON_RIGHT) {
          clickPos = { event.button.x / CELL_SIZE, event.button.y / CELL_SIZE };
          RightButtonAction(clickPos);
        }
      }
      else if (event.type == SDL_MOUSEBUTTONUP && isClicking) {
        isClicking = false;
        Point curPos = { event.button.x / CELL_SIZE, event.button.y / CELL_SIZE };
        if (curPos.x != clickPos.x || curPos.y != clickPos.y) continue;
        LeftButtonAction(clickPos);
      }
    }
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        Point pos = { i, j };
        if (isClicking && pos.x == clickPos.x && pos.y == clickPos.y)
          renderClass->DrawCell(i, j, Cell_Pressing);
        else if (gameFinished && pos.x == posMineExploded.x && pos.y == posMineExploded.y)
          renderClass->DrawCell(i, j, Cell_MineExploded);
        else
          renderClass->DrawCell(i, j, GetCellStatus(pos));
      }
    }
    renderClass->Render();
  }
}


void GameEngine::LeftButtonAction(Point pos) {
  mineField->ChangePressStatus(pos);

  // Explode a mine and end game if the cell has a mine
  if (mineField->GetMineStatus(pos)) {
    posMineExploded = pos;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++)
        mineField->ChangePressStatus({ i, j });
    }
    gameFinished = true;
  }

  else {
    // If this click is the first click of the game, place mines
    if (!minePlaced) {
      minePlaced = true;
      mineField->PlaceMines(pos);
    }
    if (mineField->GetNearMine(pos) == 0) {
      std::queue<Point> q;
      q.push(pos);
      while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        for (int i = 0; i < 8; i++) {
          Point newPos = { x + dx_8[i], y + dy_8[i] };
          if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 || newPos.y >= height) continue;
          if (mineField->GetPressStatus(newPos) == true) continue;
          if (mineField->GetMineStatus(newPos) == true) continue;
          mineField->ChangePressStatus(newPos);
          if (mineField->GetNearMine(newPos) != 0) continue;
          q.push({ newPos });
        }
      }
    }
  }
}

void GameEngine::RightButtonAction(Point pos) {
  if (mineField->GetFlagStatus(pos) == false) {
    if (mineField->GetMineStatus(pos) == true) foundMines++;
    else foundMines--;
  }
  mineField->ChangeFlagStatus(pos);
}

enum CellStatus GameEngine::GetCellStatus(Point pos) {
  if (mineField->GetPressStatus(pos) == false) {
    if (mineField->GetFlagStatus(pos) == false) return Cell_NotPressed;
    else return Cell_FlagPlaced;
  }
  else {
    if (mineField->GetMineStatus(pos) == true) return Cell_MineExposed;
    else if (mineField->GetNearMine(pos) == 0) return Cell_Pressed;
    else return (enum CellStatus)mineField->GetNearMine(pos);
  }
}