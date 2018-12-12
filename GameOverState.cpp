#pragma once

#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameOverState.hpp"

namespace CourseWork
{
	GameOverState::GameOverState(GameDataReference data) : _data(data)
	{

	}

	void GameOverState::InitializeState()
	{
		_data->asset.LoadTexture("Retry Button", RETRY_BUTTON);
		_data->asset.LoadTexture("Home Button", HOME_BUTTON);

		_retryButton.setTexture(_data->asset.GetTexture("Retry Button"));
		_homeButton.setTexture(_data->asset.GetTexture("Home Button"));

		_retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getLocalBounds().width / 2), (_data->window.getSize().y / 3) - (_retryButton.getLocalBounds().height / 2));
		_homeButton.setPosition((_data->window.getSize().x / 2) - (_homeButton.getLocalBounds().width / 2), (_data->window.getSize().y / 3 * 2) - (_homeButton.getLocalBounds().height / 2));
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window))
			{
				// Switches to the Game State by replacing the Game Over State.
				_data->machine.AddState(StateReference(new GameState(_data)), true);
			}

			if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left, _data->window))
			{
				// Switches to the Main Menu State by replacing the Game Over State.
				_data->machine.AddState(StateReference(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float deltaTime)
	{

	}

	void GameOverState::Draw(float deltaTime)
	{
		_data->window.clear(sf::Color::Red);
		_data->window.draw(_retryButton);
		_data->window.draw(_homeButton);
		_data->window.display();
	}
}