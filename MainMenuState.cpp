#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

namespace CourseWork
{
	MainMenuState::MainMenuState(GameDataReference data) : _data(data)
	{

	}

	void MainMenuState::InitializeState()
	{
		_data->asset.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_data->asset.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		_data->asset.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		_data->asset.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);

		_background.setTexture(_data->asset.GetTexture("Background"));
		_playButton.setTexture(_data->asset.GetTexture("Play Button"));
		_playButtonOuter.setTexture(_data->asset.GetTexture("Play Button Outer"));
		_title.setTexture(_data->asset.GetTexture("Game Title"));

		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + 200);
		_playButtonOuter.setPosition((SCREEN_WIDTH / 2) - (_playButtonOuter.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButtonOuter.getGlobalBounds().height / 2) + 200);
		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height * 0.1);
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
			{
				// Switches to the Game State.
				_data->machine.AddState(StateReference(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float deltaTime)
	{

	}

	void MainMenuState::Draw(float deltaTime)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_playButton);
		_data->window.draw(_playButtonOuter);
		_data->window.draw(_title);
		_data->window.display();
	}
}