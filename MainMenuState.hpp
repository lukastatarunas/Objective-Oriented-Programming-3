#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace CourseWork
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataReference data);

		void InitializeState();
		void HandleInput();

		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataReference _data;

		sf::Sprite _background;
		sf::Sprite _playButton;
		sf::Sprite _playButtonOuter;
		sf::Sprite _title;
	};
}