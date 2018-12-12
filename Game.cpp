#include "SplashState.hpp"
#include "Game.hpp"

namespace CourseWork
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->machine.AddState(StateReference(new SplashState(_data)));

		RunGame();
	}

	void Game::RunGame()
	{
		float newTime;
		float frameTime;
		float currentTime = _clock.getElapsedTime().asSeconds();
		float frameTimeTotal = 0.0f;

		while (_data->window.isOpen())
		{
			_data->machine.ProcessStateChanges();

			newTime = _clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			frameTimeTotal = frameTimeTotal + frameTime;

			while (frameTimeTotal >= deltaTime)
			{
				_data->machine.GetActiveState()->HandleInput();
				_data->machine.GetActiveState()->Update(deltaTime);

				frameTimeTotal = frameTimeTotal - deltaTime;
			}

			_data->machine.GetActiveState()->Draw(frameTimeTotal);
		}
	}
}