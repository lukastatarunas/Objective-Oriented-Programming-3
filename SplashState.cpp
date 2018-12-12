#include "DEFINITIONS.hpp"
#include "SplashState.hpp"
#include "MainMenuState.hpp"

namespace CourseWork
{
	SplashState::SplashState(GameDataReference data) : _data(data)
	{

	}

	void SplashState::InitializeState()
	{
		_data->asset.LoadTexture("Splash State Background", SPLASH_STATE_BACKGROUND_FILEPATH);

		_background.setTexture(_data->asset.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float deltaTime)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switches to the Main Menu State.
			_data->machine.AddState(StateReference(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float deltaTime)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}
}