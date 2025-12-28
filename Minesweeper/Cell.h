#pragma once
#include "Engine/Button.h"
#include "Engine/Image.h"

#include <SDL3/SDL.h>
#include <memory>

class MinesweeperCell : public Engine::Button
{
  public:
	MinesweeperCell(int X, int Y, int W, int G, int Row, int Col);

	void HandleEvent(const SDL_Event& E) override;
	void Render(SDL_Surface* Surface) override;

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

  private:
	bool hasBomb{false};
	void ReportEvent(Uint32 EventType);
	void ClearCell();
	bool isCleared{false};
	int Row;
	int Col;
	std::unique_ptr<Engine::Image> BombImage;
};