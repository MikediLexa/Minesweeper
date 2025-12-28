#pragma once
#include "Globals.h"
#include "Minesweeper/Grid.h"

#include <SDL3/SDL.h>

class MinesweeperUI {
  public:
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E) {
        Grid.HandleEvent(E);
    };

  private:
    MinesweeperGrid Grid{Config::PADDING,
                         Config::PADDING};
};