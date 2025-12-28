#include "Minesweeper/Cell.h"

#include "Engine/Image.h"
#include "Globals.h"
#include "Minesweeper/Cell.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
	: Button{x, y, w, h}, Row{Row}, Col{Col}
{
	BombImage = std::make_unique<Engine::Image>(x, y, w, h, Config::BOMB_IMAGE);
};

bool MinesweeperCell::PlaceBomb()
{
	if (hasBomb) return false;

	hasBomb = true;
	ReportEvent(UserEvents::BOMB_PLACED);
	return true;
}

void MinesweeperCell::ClearCell()
{
	if (isCleared) return;
	isCleared = true;
	SetIsDisabled(true);
	SetColor(Config::BUTTON_CLEARED_COLOR);
	ReportEvent(UserEvents::CELL_CLEARED);
}

void MinesweeperCell::HandleLeftClick() { ClearCell(); }

void MinesweeperCell::ReportEvent(Uint32 EventType)
{
	SDL_Event event{};
	event.type = EventType;
	event.user.data1 = this;
	SDL_PushEvent(&event);
}

void MinesweeperCell::HandleEvent(const SDL_Event& E)
{
	if (E.type == UserEvents::CELL_CLEARED) {
		// TODO
		std::cout << "A Cell Was Cleared\n";
	} else if (E.type == UserEvents::BOMB_PLACED) {
		// TODO
		std::cout << "A Bomb was Placed\n";
	}

	Button::HandleEvent(E);
}

void MinesweeperCell::Render(SDL_Surface* Surface)
{
	Button::Render(Surface);
	if (isCleared && hasBomb) {
		BombImage->Render(Surface);
	}
#ifdef SHOW_DEBUG_HELPERS
	else if (hasBomb) {
		BombImage->Render(Surface);
	}
#endif
}
