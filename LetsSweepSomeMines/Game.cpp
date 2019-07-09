#include "Game.h"

void Run() {
  minefield = new MineField({cellX, cellY}, mineNum);
  sizeX = cellX * CELL_SIZE;
  sizeY = cellY * CELL_SIZE;
  ConfigureRenderer();
  LoadBMPs();
  RunGame();
}

void ConfigureRenderer() {
  SDL_SetWindowSize(window, sizeX, sizeY);

  // Set size of renderer to the same as window
  SDL_RenderSetLogicalSize(renderer, sizeX, sizeY);

  // Set color of renderer to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void LoadBMPs() {
  surfaceArr[0] = SDL_LoadBMP("Images/Mine_Pressed.bmp");
  surfaceArr[1] = SDL_LoadBMP("Images/Mine_1.bmp");
  surfaceArr[2] = SDL_LoadBMP("Images/Mine_2.bmp");
  surfaceArr[3] = SDL_LoadBMP("Images/Mine_3.bmp");
  surfaceArr[4] = SDL_LoadBMP("Images/Mine_4.bmp");
  surfaceArr[5] = SDL_LoadBMP("Images/Mine_5.bmp");
  surfaceArr[6] = SDL_LoadBMP("Images/Mine_6.bmp");
  surfaceArr[7] = SDL_LoadBMP("Images/Mine_7.bmp");
  surfaceArr[8] = SDL_LoadBMP("Images/Mine_8.bmp");
  surfaceArr[9] = SDL_LoadBMP("Images/Mine_MineExposed.bmp");
  surfaceArr[10] = SDL_LoadBMP("Images/Mine_Pressing.bmp");
  surfaceArr[11] = SDL_LoadBMP("Images/Mine_NotPressed.bmp");
  surfaceArr[12] = SDL_LoadBMP("Images/Mine_FlagPlaced.bmp");
  surfaceArr[13] = SDL_LoadBMP("Images/Mine_MineExploded.bmp");
}

void Render() {
  // Clear the window and make it all white
  SDL_RenderClear(renderer);

  // Render cells
  for (int yPos = 0; yPos < cellY; yPos++) {
    for (int xPos = 0; xPos < cellX; xPos++) {
      SDL_Texture* texture;
      if (minefield->GetClickStatus({ xPos, yPos }) == 0) {
        if (minefield->GetFlagStatus({xPos, yPos}) == true)
          texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[12]);
        else
          texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[11]);
      }
      else if (minefield->GetClickStatus({xPos, yPos}) == 1)
        texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[10]);
      else {
        if (minefield->GetMineStatus({xPos, yPos}) == true) {
          if (minefield->GetExplodedPos() == std::make_pair(xPos, yPos))
            texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[13]);
          else
          texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[9]);
        }
        else {
          int mineNum = minefield->GetNearMine({xPos, yPos});
          texture = SDL_CreateTextureFromSurface(renderer, surfaceArr[mineNum]);
        }
      }
      SDL_Rect rect;
      rect.x = xPos * CELL_SIZE, rect.y = yPos * CELL_SIZE, rect.w = CELL_SIZE, rect.h = CELL_SIZE;
      SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
  }
  // Render the changes above
  SDL_RenderPresent(renderer);
}

void RunGame() {
  bool loop = true;
  bool isClicking = false;
  int cellPosX = -1, cellPosY = -1;

  while (loop) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        loop = false;
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (isClicking) continue;
          isClicking = true;
          cellPosX = event.button.x / 32;
          cellPosY = event.button.y / 32;
          std::pair<int, int> coor = std::make_pair(cellPosX, cellPosY);
          if (minefield->GetClickStatus(coor) == 2) continue;
          minefield->ChangeCellClickStatus(coor, 1);
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          cellPosX = event.button.x / 32;
          cellPosY = event.button.y / 32;
          std::pair<int, int> coor = std::make_pair(cellPosX, cellPosY);
          minefield->RightButtonAction(coor);
        }
      } else if (event.type == SDL_MOUSEBUTTONUP && isClicking) {
        isClicking = false;
        int curPosX = event.button.x / 32;
        int curPosY = event.button.y / 32;
        std::pair<int, int> coor = std::make_pair(curPosX, curPosY);
        std::pair<int, int> coorPrev = std::make_pair(cellPosX, cellPosY);
        if (coor != coorPrev) {
          if (minefield->GetClickStatus(coorPrev) == 2) continue;
          minefield->ChangeCellClickStatus(coorPrev, 0);
          continue;
        }
        if (minefield->GetClickStatus(coor) == 2) continue;
        minefield->LeftButtonAction(coor);
      }
    }

    Render();

    // Add a 16msec delay to make our game run at ~60 fps
    SDL_Delay(16);
  }
}