#pragma once
#include "Engine/Random.h"
#include "Globals.h"
#include "Minesweeper/Cell.h"

#include <SDL3/SDL.h>
#include <vector>

class MinesweeperGrid
{
  public:
	MinesweeperGrid(int x, int y)
	{
		Children.reserve(Config::GRID_COLUMNS * Config::GRID_ROWS);
		for (int Col{1}; Col <= Config::GRID_COLUMNS; Col++) {
			for (int Row{1}; Row <= Config::GRID_ROWS; Row++) {
				constexpr int Spacing{Config::CELL_SIZE + Config::PADDING};
				Children.emplace_back(
					x + (Spacing) * (Col - 1), y + (Spacing) * (Row - 1),
					Config::CELL_SIZE, Config::CELL_SIZE, Row, Col);
			}
		}
		PlaceBombs();
	}

	void Render(SDL_Surface* Surface)
	{
		for (auto& Child : Children) {
			Child.Render(Surface);
		}
	}

	void HandleEvent(const SDL_Event& E)
	{
		for (auto& Child : Children) {
			Child.HandleEvent(E);
		}
	}

	void PlaceBombs()
	{
		int BombsToPlace{Config::BOMB_COUNT};
		while (BombsToPlace > 0) {
			const size_t RandomIndex{
				Engine::Random::Int(0, Children.size() - 1)};
			if (Children[RandomIndex].PlaceBomb()) {
				BombsToPlace--;
			}
		}
	};

	std::vector<MinesweeperCell> Children;
};
