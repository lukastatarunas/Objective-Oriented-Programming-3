#pragma once

#include <SFML/Graphics.hpp>

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace CourseWork
{
	struct GameData
	{
		sf::RenderWindow window;
		StateMachine machine;
		AssetManager asset;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataReference;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		GameDataReference _data = std::make_shared<GameData>();

		sf::Clock _clock;

		// Updates 60 times per second.
		const float deltaTime = 1.0f / 60.0f;

		void RunGame();
	};
}