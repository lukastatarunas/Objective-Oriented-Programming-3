#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace CourseWork
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataReference data);

		void InitializeState();
		void HandleInput();

		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataReference _data;

		sf::Sprite _background;
		sf::Sprite _resumeButton;
		sf::Sprite _homeButton;
	};
}