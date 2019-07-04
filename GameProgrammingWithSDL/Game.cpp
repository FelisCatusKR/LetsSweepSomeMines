#include "Game.h"

void Render() {
  // Clear the window and make it all white
  SDL_RenderClear(renderer);

  // Change color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  // Render a "player"
  SDL_RenderFillRect(renderer, &playerPos);

  // Change its color to green
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

  // Render the changes above
  SDL_RenderPresent(renderer);
}

void RunGame()
{
  bool loop = true;

  while (loop)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        loop = false;
      else if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
          ++playerPos.x;
          break;
        case SDLK_LEFT:
          --playerPos.x;
          break;
          // Remeber 0,0 in SDL is left-top. So when the user pressus down, the y need to increase
        case SDLK_DOWN:
          ++playerPos.y;
          break;
        case SDLK_UP:
          --playerPos.y;
          break;
        default:
          break;
        }
      }
    }

    Render();

    // Add a 16msec delay to make our game run at ~60 fps
    SDL_Delay(16);
  }
}