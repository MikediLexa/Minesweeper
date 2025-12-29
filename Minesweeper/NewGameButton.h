#pragma once
#include "Engine/Button.h"
#include "Engine/Text.h"
#include "Globals.h"

#include <SDL3/SDL.h>

class NewGameButton : public Engine::Button
{
  public:
	NewGameButton(int x, int y, int w, int h)
		: Button{x, y, w, h},
		  Text{x, y, w, h, "NEW GAME", {255, 255, 255, 255}, 20.0f}
	{
	}

	void Render(SDL_Surface* Surface) override
	{
		Button::Render(Surface);
		Text.Render(Surface);
	}

  protected:
	void HandleLeftClick() override
	{
		SDL_Event E{};
		E.type = UserEvents::NEW_GAME;
		SDL_PushEvent(&E);
	}

  private:
	Engine::Text Text;
};