#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "AI.hpp"

namespace CourseWork
{
	class GameState : public State
	{
	public:
		GameState(GameDataReference data);

		void InitializeState();
		void HandleInput();

		void Update(float deltaTime);
		void Draw(float deltaTime);

	private:
		void InitializeGridPieces();
		void CheckAndPlacePiece();

		void CheckIfSomeoneHasWon(int turn);
		void WinningOptions(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

		GameDataReference _data;

		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;
		sf::Sprite _gridPieces[3][3];

		int _gridArray[3][3];
		int turn;
		int gameState;

		AI *ai;

		sf::Clock _clock;
	};
}