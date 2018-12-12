#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace CourseWork
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataReference data);

		void InitializeState();
		void HandleInput();

		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataReference _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
	};
}