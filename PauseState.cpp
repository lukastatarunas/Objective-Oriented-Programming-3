#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

namespace CourseWork
{
	PauseState::PauseState(GameDataReference data) : _data(data)
	{

	}

	void PauseState::InitializeState()
	{
		_data->asset.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		_data->asset.LoadTexture("Resume Button", RESUME_BUTTON);
		_data->asset.LoadTexture("Home Button", HOME_BUTTON);

		_background.setTexture(_data->asset.GetTexture("Pause Background"));
		_resumeButton.setTexture(_data->asset.GetTexture("Resume Button"));
		_homeButton.setTexture(_data->asset.GetTexture("Home Button"));

		_resumeButton.setPosition((_data->window.getSize().x / 2) - (_resumeButton.getLocalBounds().width / 2), (_data->window.getSize().y / 3) - (_resumeButton.getLocalBounds().height / 2));
		_homeButton.setPosition((_data->window.getSize().x / 2) - (_homeButton.getLocalBounds().width / 2), (_data->window.getSize().y / 3 * 2) - (_homeButton.getLocalBounds().height / 2));
	}

	void PauseState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_resumeButton, sf::Mouse::Left, _data->window))
			{
				// Resumes the game by popping of the current state (Pause State).
				_data->machine.RemoveState();
			}

			if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left, _data->window))
			{
				// Removes the Pause State off the stack.
				_data->machine.RemoveState();

				// Switches to the Main Menu State By Replacing The Game State.
				_data->machine.AddState(StateReference(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::Update(float deltaTime)
	{

	}

	void PauseState::Draw(float deltaTime)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_resumeButton);
		_data->window.draw(_homeButton);
		_data->window.display();
	}
}