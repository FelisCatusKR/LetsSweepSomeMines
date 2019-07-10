#include "GameEngine.h"

bool GameEngine::Init() {
  renderClass = new RenderClass;
  if (renderClass->Init() == false) return false;
  return true;
}

bool GameEngine::GameLoop() {
  if (renderClass->MainMenu() == false) return false;
  while (!MainMenu()) {
    mineField = new MineField(diffStruct[diff].w, diffStruct[diff].h,
                              diffStruct[diff].totalM);
    if (renderClass->NewGame(diffStruct[diff].w, diffStruct[diff].h) == false)
      return false;
    RunGame();
    delete mineField;
    if (renderClass->MainMenu() == false) return false;
  }
  return true;
}

bool GameEngine::MainMenu() {
  bool loop = true;
  bool quit = false;
  bool isClicking = false;
  Point clickPos = {-1, -1};

  while (loop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        loop = false;
        quit = true;
      } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                 event.button.button == SDL_BUTTON_LEFT) {
        if (isClicking) continue;
        isClicking = true;
        clickPos = {event.button.x, event.button.y};
      } else if (event.type == SDL_MOUSEBUTTONUP && isClicking) {
        isClicking = false;
        clickPos = {event.button.x, event.button.y};

        if (clickPos.x < BUTTON_SPACE_X ||
            clickPos.x >= BUTTON_SPACE_X + MENUBUTTON_WIDTH)
          continue;
        if (clickPos.y >= BUTTON_SPACE_Y * 1 + MENUBUTTON_HEIGHT * 0 &&
            clickPos.y < BUTTON_SPACE_Y * 1 + MENUBUTTON_HEIGHT * 1)
          diff = Easy;
        if (clickPos.y >= BUTTON_SPACE_Y * 2 + MENUBUTTON_HEIGHT * 1 &&
            clickPos.y < BUTTON_SPACE_Y * 2 + MENUBUTTON_HEIGHT * 2)
          diff = Normal;
        if (clickPos.y >= BUTTON_SPACE_Y * 3 + MENUBUTTON_HEIGHT * 2 &&
            clickPos.y < BUTTON_SPACE_Y * 3 + MENUBUTTON_HEIGHT * 3)
          diff = Hard;
        loop = false;
      }
    }
    for (int i = 0; i < 3; i++) {
      switch (i) {
        case 0:
          renderClass->DrawCell(i, Main_Easy);
          if (isClicking) {
            if (clickPos.x >= BUTTON_SPACE_X &&
                clickPos.x < BUTTON_SPACE_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, Main_Easy_Pressed);
          }
          break;
        case 1:
          renderClass->DrawCell(i, Main_Normal);
          if (isClicking) {
            if (clickPos.x >= BUTTON_SPACE_X &&
                clickPos.x < BUTTON_SPACE_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, Main_Normal_Pressed);
          }
          break;
        case 2:
          renderClass->DrawCell(i, Main_Hard);
          if (isClicking) {
            if (clickPos.x >= BUTTON_SPACE_X &&
                clickPos.x < BUTTON_SPACE_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    BUTTON_SPACE_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, Main_Hard_Pressed);
          }
          break;
      }
    }
    renderClass->Render();
  }

  return quit;
}

void GameEngine::RunGame() {
  bool loop = true;
  bool isClicking = false;
  Point clickPos = {-1, -1};

  while (loop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        loop = false;
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (isClicking) continue;
          isClicking = true;
          clickPos = {event.button.x / CELL_SIZE, event.button.y / CELL_SIZE};
          if (mineField->GetPressStatus(clickPos) == true) {
            isClicking = false;
            continue;
          }
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          clickPos = {event.button.x / CELL_SIZE, event.button.y / CELL_SIZE};
          RightButtonAction(clickPos);
        }
      } else if (event.type == SDL_MOUSEBUTTONUP && isClicking) {
        isClicking = false;
        Point curPos = {event.button.x / CELL_SIZE, event.button.y / CELL_SIZE};
        if (curPos.x != clickPos.x || curPos.y != clickPos.y) continue;
        LeftButtonAction(clickPos);
      }
    }
    for (int i = 0; i < diffStruct[diff].w; i++) {
      for (int j = 0; j < diffStruct[diff].h; j++) {
        Point pos = {i, j};
        if (isClicking && pos.x == clickPos.x && pos.y == clickPos.y)
          renderClass->DrawCell(mineField->CalcIndex(pos), Cell_Pressing);
        else
          renderClass->DrawCell(mineField->CalcIndex(pos), GetCellStatus(pos));
      }
    }
    if (gameFinished) {
      int explodedPos = mineField->CalcIndex(mineField->GetMineExploded());
      renderClass->DrawCell(explodedPos, Cell_MineExploded);
    }
    renderClass->Render();
  }
}

void GameEngine::LeftButtonAction(Point pos) {
  mineField->ChangePressStatus(pos);

  // Explode a mine and end game if the cell has a mine
  if (mineField->GetMineStatus(pos)) {
    mineField->ChangeMineExploded(pos);
    for (int i = 0; i < diffStruct[diff].w; i++) {
      for (int j = 0; j < diffStruct[diff].h; j++)
        mineField->ChangePressStatus({i, j});
    }
    gameFinished = true;
  }

  else {
    // If this click is the first click of the game, place mines
    if (!mineField->GetMinePlaced()) {
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
          Point newPos = {x + dx_8[i], y + dy_8[i]};
          if (newPos.x < 0 || newPos.x >= diffStruct[diff].w || newPos.y < 0 ||
              newPos.y >= diffStruct[diff].h)
            continue;
          if (mineField->GetPressStatus(newPos) == true) continue;
          if (mineField->GetMineStatus(newPos) == true) continue;
          mineField->ChangePressStatus(newPos);
          if (mineField->GetNearMine(newPos) != 0) continue;
          q.push({newPos});
        }
      }
    }
  }
}

void GameEngine::RightButtonAction(Point pos) {
  if (mineField->GetFlagStatus(pos) == false) {
    if (mineField->GetMineStatus(pos) == true)
      foundMines++;
    else
      foundMines--;
  }
  mineField->ChangeFlagStatus(pos);
}

enum CellStatus GameEngine::GetCellStatus(Point pos) {
  if (mineField->GetPressStatus(pos) == false) {
    if (mineField->GetFlagStatus(pos) == false)
      return Cell_NotPressed;
    else
      return Cell_FlagPlaced;
  } else {
    if (mineField->GetMineStatus(pos) == true)
      return Cell_MineExposed;
    else if (mineField->GetNearMine(pos) == 0)
      return Cell_Pressed;
    else
      return (enum CellStatus)mineField->GetNearMine(pos);
  }
}