#include "GameEngine.h"

bool GameEngine::Init() {
  renderClass = new RenderClass;
  if (renderClass->Init() == false) return false;
  return true;
}

void GameEngine::GameLoop() {
  while (true) {
    renderClass->MainMenu();
    bool isQuit = MainMenu();
    if (isQuit) break;
    bool isGameQuit = false;
    while (!isGameQuit) {
      mineField = new MineField(diffStruct[static_cast<int>(diff)].w,
                                diffStruct[static_cast<int>(diff)].h,
                                diffStruct[static_cast<int>(diff)].totalM);
      renderClass->NewGame(diffStruct[static_cast<int>(diff)].w,
                           diffStruct[static_cast<int>(diff)].h);
      isGameQuit = RunGame();
      delete mineField;
    }
  }
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

        if (clickPos.x < MENUBUTTON_MARGIN_X ||
            clickPos.x >= MENUBUTTON_MARGIN_X + MENUBUTTON_WIDTH)
          continue;
        if (clickPos.y >= MENUBUTTON_MARGIN_Y * 1 + MENUBUTTON_HEIGHT * 0 &&
            clickPos.y < MENUBUTTON_MARGIN_Y * 1 + MENUBUTTON_HEIGHT * 1)
          diff = Difficulty::Easy;
        if (clickPos.y >= MENUBUTTON_MARGIN_Y * 2 + MENUBUTTON_HEIGHT * 1 &&
            clickPos.y < MENUBUTTON_MARGIN_Y * 2 + MENUBUTTON_HEIGHT * 2)
          diff = Difficulty::Normal;
        if (clickPos.y >= MENUBUTTON_MARGIN_Y * 3 + MENUBUTTON_HEIGHT * 2 &&
            clickPos.y < MENUBUTTON_MARGIN_Y * 3 + MENUBUTTON_HEIGHT * 3)
          diff = Difficulty::Hard;
        loop = false;
      }
    }
    for (int i = 0; i < 3; i++) {
      switch (i) {
        case 0:
          renderClass->DrawCell(i, ButtonStatus::Main_Easy);
          if (isClicking) {
            if (clickPos.x >= MENUBUTTON_MARGIN_X &&
                clickPos.x < MENUBUTTON_MARGIN_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, ButtonStatus::Main_Easy_Pressed);
          }
          break;
        case 1:
          renderClass->DrawCell(i, ButtonStatus::Main_Normal);
          if (isClicking) {
            if (clickPos.x >= MENUBUTTON_MARGIN_X &&
                clickPos.x < MENUBUTTON_MARGIN_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, ButtonStatus::Main_Normal_Pressed);
          }
          break;
        case 2:
          renderClass->DrawCell(i, ButtonStatus::Main_Hard);
          if (isClicking) {
            if (clickPos.x >= MENUBUTTON_MARGIN_X &&
                clickPos.x < MENUBUTTON_MARGIN_X + MENUBUTTON_WIDTH &&
                clickPos.y >=
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * i &&
                clickPos.y <
                    MENUBUTTON_MARGIN_Y * (i + 1) + MENUBUTTON_HEIGHT * (i + 1))
              renderClass->DrawCell(i, ButtonStatus::Main_Hard_Pressed);
          }
          break;
      }
    }
    renderClass->Render();
  }

  return quit;
}

bool GameEngine::RunGame() {
  bool loop = true;
  bool quit = false;
  bool isClicking = false;
  Point clickPos = {-1, -1};
  ClickedPos prevClickedPos = ClickedPos::Background;
  timer = new Timer;
  gameStatus = GameStatus::NotFinished;
  curTime = 0.0;
  int restartButtonIndex = diffStruct[static_cast<int>(diff)].w *
                           diffStruct[static_cast<int>(diff)].h;

  while (loop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        loop = false;
        quit = true;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (isClicking) continue;
          isClicking = true;
          prevClickedPos = CheckClickedPos(event);
          if (prevClickedPos == ClickedPos::Cell) {
            clickPos = {event.button.x / CELL_SIZE,
                        (event.button.y - GAME_HEADER_HEIGHT) / CELL_SIZE};
            if (mineField->GetPressStatus(clickPos) == true) {
              isClicking = false;
              continue;
            }
          } else if (prevClickedPos == ClickedPos::Button) {
          } else
            isClicking = false;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          if (gameStatus != GameStatus::NotFinished) continue;
          if (CheckClickedPos(event) != ClickedPos::Cell) continue;
          clickPos = {event.button.x / CELL_SIZE,
                      (event.button.y - GAME_HEADER_HEIGHT) / CELL_SIZE};
          RightButtonAction(clickPos);
        }
      } else if (event.type == SDL_MOUSEBUTTONUP && isClicking) {
        isClicking = false;
        ClickedPos curClickedPos = CheckClickedPos(event);
        if (curClickedPos != prevClickedPos) continue;
        if (curClickedPos == ClickedPos::Cell &&
            gameStatus == GameStatus::NotFinished)
          LeftButtonAction(clickPos);
        else if (curClickedPos == ClickedPos::Button)
          loop = false;
      }
    }
    for (int i = 0; i < diffStruct[static_cast<int>(diff)].w; i++) {
      for (int j = 0; j < diffStruct[static_cast<int>(diff)].h; j++) {
        Point pos = {i, j};
        if (isClicking && prevClickedPos == ClickedPos::Cell &&
            pos.x == clickPos.x && pos.y == clickPos.y)
          renderClass->DrawCell(mineField->CalcIndex(pos),
                                ButtonStatus::Cell_Pressing);
        else
          renderClass->DrawCell(mineField->CalcIndex(pos), GetCellStatus(pos));
      }
    }
    if (gameStatus == GameStatus::Lose) {
      int explodedPos = mineField->CalcIndex(mineField->GetMineExploded());
      renderClass->DrawCell(explodedPos, ButtonStatus::Cell_MineExploded);
    }

    if (isClicking && prevClickedPos == ClickedPos::Button)
      renderClass->DrawCell(restartButtonIndex, ButtonStatus::Restart_Pressing);
    else if (gameStatus == GameStatus::Win)
      renderClass->DrawCell(restartButtonIndex, ButtonStatus::Restart_Win);
    else if (gameStatus == GameStatus::Lose)
      renderClass->DrawCell(restartButtonIndex, ButtonStatus::Restart_Lose);
    else
      renderClass->DrawCell(restartButtonIndex,
                            ButtonStatus::Restart_NotPressed);
    if (timer->GetInit() == true && gameStatus == GameStatus::NotFinished)
      curTime = timer->GetDelta();
    renderClass->DrawRemainCount(mineField->GetRemainFlagCount());
    renderClass->DrawTimer(static_cast<int>(curTime));
    renderClass->Render();
  }
  delete timer;
  return quit;
}

void GameEngine::LeftButtonAction(Point pos) {
  mineField->ChangePressStatus(pos);

  // Explode a mine and change the game status to Lose if the cell has a mine
  if (mineField->GetMineStatus(pos)) {
    mineField->ChangeMineExploded(pos);
    for (int i = 0; i < diffStruct[static_cast<int>(diff)].w; i++) {
      for (int j = 0; j < diffStruct[static_cast<int>(diff)].h; j++)
        mineField->ChangePressStatus({i, j});
    }
    gameStatus = GameStatus::Lose;
  }

  else {
    // If this click is the first click of the game, place mines and start a
    // timer
    if (!mineField->GetMinePlaced()) {
      mineField->PlaceMines(pos);
      timer->Init();
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
          if (newPos.x < 0 ||
              newPos.x >= diffStruct[static_cast<int>(diff)].w ||
              newPos.y < 0 || newPos.y >= diffStruct[static_cast<int>(diff)].h)
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
  if (mineField->GetPressStatus(pos)) return;
  mineField->ChangeFlagStatus(pos);
  if (mineField->GetFoundMineCount() == mineField->GetTotalMineCount()) {
    for (int i = 0; i < diffStruct[static_cast<int>(diff)].w; i++) {
      for (int j = 0; j < diffStruct[static_cast<int>(diff)].h; j++) {
        Point tmpPos = {i, j};
        if (!mineField->GetFlagStatus(tmpPos))
          mineField->ChangePressStatus(tmpPos);
      }
    }
    gameStatus = GameStatus::Win;
  }
}

ButtonStatus GameEngine::GetCellStatus(Point pos) {
  if (mineField->GetPressStatus(pos) == false) {
    if (mineField->GetFlagStatus(pos) == false)
      return ButtonStatus::Cell_NotPressed;
    else
      return ButtonStatus::Cell_FlagPlaced;
  } else {
    if (mineField->GetMineStatus(pos) == true)
      return ButtonStatus::Cell_MineExposed;
    else if (mineField->GetNearMine(pos) == 0)
      return ButtonStatus::Cell_Pressed;
    else
      return static_cast<ButtonStatus>(mineField->GetNearMine(pos));
  }
}

GameEngine::ClickedPos GameEngine::CheckClickedPos(SDL_Event event) {
  int buttonMarginX =
      (CELL_SIZE * diffStruct[static_cast<int>(diff)].w - RESTARTBUTTON_WIDTH) /
      2;
  if (event.button.y >= GAME_HEADER_HEIGHT)
    return ClickedPos::Cell;
  else if (event.button.y >= RESTARTBUTTON_PADDING &&
           event.button.y < RESTARTBUTTON_PADDING + RESTARTBUTTON_HEIGHT &&
           event.button.x >= buttonMarginX &&
           event.button.x < buttonMarginX + RESTARTBUTTON_WIDTH)
    return ClickedPos::Button;
  else
    return ClickedPos::Background;
}