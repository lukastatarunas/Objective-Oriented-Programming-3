#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace CourseWork
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataReference data);

		void InitializeState();
		void HandleInput();

		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		GameDataReference _data;

		sf::Clock _clock;
		sf::Sprite _background;
	};
}