#include "Minesweeper/Cell.h"

#include "Engine/Image.h"
#include "Engine/Text.h"
#include "Globals.h"
#include "Minesweeper/Cell.h"
#include "SDL3/SDL_events.h"

#include <SDL3/SDL.h>
#include <memory>
#include <string>

MinesweeperCell::MinesweeperCell(int x, int y, int w, int h, int Row, int Col)
	: Button{x, y, w, h}, Row{Row}, Col{Col}
{
	FlagImage = std::make_unique<Engine::Image>(x, y, w, h, Config::FLAG_IMAGE);
	BombImage = std::make_unique<Engine::Image>(x, y, w, h, Config::BOMB_IMAGE);
	Text = std::make_unique<Engine::Text>(x, y, w, h,
										  std::to_string(AdjacentBombs),
										  Config::TEXT_COLORS[AdjacentBombs]);
};

void MinesweeperCell::HandleBombPlaced(const SDL_UserEvent& E)
{
	const auto* Cell{static_cast<MinesweeperCell*>(E.data1)};
	if (isAdjacent(Cell)) {
		AdjacentBombs++;
		Text->SetText(std::to_string(AdjacentBombs),
					  Config::TEXT_COLORS[AdjacentBombs]);
	}
}

void MinesweeperCell::HandleCellCleared(const SDL_UserEvent& E)
{
	const auto* Cell{static_cast<MinesweeperCell*>(E.data1)};
	if (Cell->GetHasBomb()) return;
	if (isAdjacent(Cell) && Cell->AdjacentBombs == 0) {
		ClearCell();
	}
}

bool MinesweeperCell::isAdjacent(const MinesweeperCell* Other) const
{
	return !(Other == this) && std::abs(GetRow() - Other->GetRow()) <= 1 &&
		   std::abs(GetCol() - Other->GetCol()) <= 1;
}

void MinesweeperCell::Reset()
{
	isCleared = false;
	hasFlag = false;
	hasBomb = false;
	AdjacentBombs = 0;
	SetIsDisabled(false);
	SetColor(Config::BUTTON_COLOR);
	Text->SetText(std::to_string(AdjacentBombs),
				  Config::TEXT_COLORS[AdjacentBombs]);
}

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

void MinesweeperCell::HandleLeftClick()
{
	if (!hasFlag) {
		ClearCell();
	}
}

void MinesweeperCell::HandleRightClick()
{
	if (hasFlag) {
		ReportEvent(UserEvents::FLAG_CLEARED);
		hasFlag = false;
	} else {
		ReportEvent(UserEvents::FLAG_PLACED);
		hasFlag = true;
	}
}

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
		HandleCellCleared(E.user);
	} else if (E.type == UserEvents::BOMB_PLACED) {
		HandleBombPlaced(E.user);
	} else if (E.type == UserEvents::GAME_WON) {
		if (hasBomb) {
			hasFlag = true;
			SetColor(Config::BUTTON_SUCCESS_COLOR);
		}
		SetIsDisabled(true);
	} else if (E.type == UserEvents::GAME_LOST) {
		if (hasBomb) {
			isCleared = true;
			SetColor(Config::BUTTON_FAILURE_COLOR);
		}
		SetIsDisabled(true);
	}
	Button::HandleEvent(E);
}

void MinesweeperCell::Render(SDL_Surface* Surface)
{
	Button::Render(Surface);
	if (hasFlag) {
		FlagImage->Render(Surface);
	} else if (isCleared && hasBomb) {
		BombImage->Render(Surface);
	} else if (isCleared && AdjacentBombs > 0) {
		Text->Render(Surface);
	}
#ifdef SHOW_DEBUG_HELPERS
	else if (hasBomb) {
		BombImage->Render(Surface);
	}
#endif
}
