#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

namespace CourseWork
{
	GameState::GameState(GameDataReference data) : _data(data)
	{

	}

	void GameState::InitializeState()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		ai = new AI(turn, _data);

		_data->asset.LoadTexture("Pause Button", PAUSE_BUTTON);
		_data->asset.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		_data->asset.LoadTexture("X Piece", X_PIECE_FILEPATH);
		_data->asset.LoadTexture("O Piece", O_PIECE_FILEPATH);
		_data->asset.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		_data->asset.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		_background.setTexture(_data->asset.GetTexture("Background"));
		_pauseButton.setTexture(_data->asset.GetTexture("Pause Button"));
		_gridSprite.setTexture(_data->asset.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		InitializeGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left, _data->window))
			{
				// Switches to the Pause State.
				_data->machine.AddState(StateReference(new PauseState(_data)), false);
			}

			else if (_data->input.IsSpriteClicked(_gridSprite, sf::Mouse::Left, _data->window))
			{
				if (gameState == STATE_PLAYING)
				{
					CheckAndPlacePiece();
				}
			}
		}
	}

	void GameState::Update(float deltaTime)
	{
		if (gameState == STATE_DRAW || gameState == STATE_WIN || gameState == STATE_LOSE)
		{
			if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
			{
				// Switches to the Game Over State.
				_data->machine.AddState(StateReference(new GameOverState(_data)), true);
			}
		}
	}

	void GameState::Draw(float deltaTime)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_pauseButton);
		_data->window.draw(_gridSprite);

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_data->window.draw(_gridPieces[x][y]);
			}
		}

		_data->window.display();
	}

	void GameState::InitializeGridPieces()
	{
		sf::Vector2u temporarySpriteSize = _data->asset.GetTexture("X Piece").getSize();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridPieces[x][y].setTexture(_data->asset.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (temporarySpriteSize.x * x) - 7, _gridSprite.getPosition().y + (temporarySpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::CheckAndPlacePiece()
	{
		sf::Vector2i clickPoint = _data->input.GetMousePosition(_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalClickPosition = sf::Vector2f(clickPoint.x - gapOutsideOfGrid.x, clickPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column;
		int row;

		// Checks which column the Player has clicked.
		if (gridLocalClickPosition.x < gridSectionSize.x) // First Column.
		{
			column = 1;
		}

		else if (gridLocalClickPosition.x < gridSectionSize.x * 2) // Second Column.
		{
			column = 2;
		}

		else if (gridLocalClickPosition.x < gridSize.width) // Third Column.
		{
			column = 3;
		}

		// Checks which row the Player has clicked.
		if (gridLocalClickPosition.y < gridSectionSize.y) // First Row.
		{
			row = 1;
		}

		else if (gridLocalClickPosition.y < gridSectionSize.y * 2) // Second Row.
		{
			row = 2;
		}

		else if (gridLocalClickPosition.y < gridSize.height) // Third Row.
		{
			row = 3;
		}

		if (_gridArray[column - 1][row - 1] == EMPTY_PIECE)
		{
			_gridArray[column - 1][row - 1] = turn;

			if (turn == PLAYER_PIECE)
			{
				_gridPieces[column - 1][row - 1].setTexture(_data->asset.GetTexture("X Piece"));

				CheckIfSomeoneHasWon(turn);
			}

			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::CheckIfSomeoneHasWon(int turn)
	{
		WinningOptions(0, 0, 1, 0, 2, 0, turn);
		WinningOptions(0, 1, 1, 1, 2, 1, turn);
		WinningOptions(0, 2, 1, 2, 2, 2, turn);
		WinningOptions(0, 0, 0, 1, 0, 2, turn);
		WinningOptions(1, 0, 1, 1, 1, 2, turn);
		WinningOptions(2, 0, 2, 1, 2, 2, turn);
		WinningOptions(0, 0, 1, 1, 2, 2, turn);
		WinningOptions(0, 2, 1, 1, 2, 0, turn);

		if (gameState != STATE_WIN)
		{
			gameState = STATE_AI_PLAYING;

			ai->PlacePiece(&_gridArray, _gridPieces, &gameState);

			WinningOptions(0, 0, 1, 0, 2, 0, AI_PIECE);
			WinningOptions(0, 1, 1, 1, 2, 1, AI_PIECE);
			WinningOptions(0, 2, 1, 2, 2, 2, AI_PIECE);
			WinningOptions(0, 0, 0, 1, 0, 2, AI_PIECE);
			WinningOptions(1, 0, 1, 1, 1, 2, AI_PIECE);
			WinningOptions(2, 0, 2, 1, 2, 2, AI_PIECE);
			WinningOptions(0, 0, 1, 1, 2, 2, AI_PIECE);
			WinningOptions(0, 2, 1, 1, 2, 0, AI_PIECE);
		}

		int emptyGridSpaces = 9;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (_gridArray[x][y] != EMPTY_PIECE)
				{
					emptyGridSpaces--;
				}
			}
		}

		// Checks if the game is a draw.
		if (emptyGridSpaces == 0 && (gameState != STATE_WIN) && (gameState != STATE_LOSE))
		{
			gameState = STATE_DRAW;
		}

		// Checks if the game is over.
		if (gameState == STATE_DRAW || gameState == STATE_WIN || gameState == STATE_LOSE)
		{
			// Shows game over.
			_clock.restart();
		}

		printf("%d\n", gameState);
	}

	void GameState::WinningOptions(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == _gridArray[x1][y1] && pieceToCheck == _gridArray[x2][y2] && pieceToCheck == _gridArray[x3][y3])
		{
			std::string winningPieceString;

			if (pieceToCheck == O_PIECE)
			{
				winningPieceString = "O Winning Piece";
			}

			else
			{
				winningPieceString = "X Winning Piece";
			}

			_gridPieces[x1][y1].setTexture(_data->asset.GetTexture(winningPieceString));
			_gridPieces[x2][y2].setTexture(_data->asset.GetTexture(winningPieceString));
			_gridPieces[x3][y3].setTexture(_data->asset.GetTexture(winningPieceString));

			if (pieceToCheck == PLAYER_PIECE)
			{
				gameState = STATE_WIN;
			}

			else
			{
				gameState = STATE_LOSE;
			}
		}
	}
}