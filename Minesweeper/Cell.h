#pragma once
#include "Engine/Button.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

#include <SDL3/SDL.h>
#include <memory>

class MinesweeperCell : public Engine::Button
{
  public:
	MinesweeperCell(int X, int Y, int W, int G, int Row, int Col);

	void HandleEvent(const SDL_Event& E) override;
	void Render(SDL_Surface* Surface) override;

	void Reset();

	bool PlaceBomb();

	[[nodiscard]]
	bool GetHasBomb() const
	{
		return hasBomb;
	}

	[[nodiscard]]
	int GetRow() const
	{
		return Row;
	}

	[[nodiscard]]
	int GetCol() const
	{
		return Col;
	}

  protected:
	void HandleLeftClick() override;
	void HandleRightClick() override;

  private:
	void HandleCellCleared(const SDL_UserEvent& E);
	void HandleBombPlaced(const SDL_UserEvent& E);
	bool isAdjacent(const MinesweeperCell* Other) const;
	void ClearCell();
	void ReportEvent(Uint32 EventType);

	int AdjacentBombs{0};
	int Row;
	int Col;
	bool hasBomb{false};
	bool isCleared{false};
	bool hasFlag{false};
	std::unique_ptr<Engine::Image> FlagImage;
	std::unique_ptr<Engine::Image> BombImage;
	std::unique_ptr<Engine::Text> Text;
};