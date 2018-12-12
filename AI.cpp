#include "DEFINITIONS.hpp"
#include "AI.hpp"

namespace CourseWork
{
	AI::AI(int playerPiece, GameDataReference data)
	{
		_data = data;
		this->playerPiece = playerPiece;

		if (playerPiece == O_PIECE)
		{
			aiPiece = X_PIECE;
		}

		else
		{
			aiPiece = O_PIECE;
		}

		checkGameVector.push_back({ 0, 2, 1, 2, 2, 2 });
		checkGameVector.push_back({ 0, 2, 0, 1, 0, 0 });
		checkGameVector.push_back({ 0, 2, 1, 1, 2, 0 });
		checkGameVector.push_back({ 2, 2, 1, 2, 0, 2 });
		checkGameVector.push_back({ 2, 2, 2, 1, 2, 0 });
		checkGameVector.push_back({ 2, 2, 1, 1, 0, 0 });
		checkGameVector.push_back({ 0, 0, 0, 1, 0, 2 });
		checkGameVector.push_back({ 0, 0, 1, 0, 2, 0 });
		checkGameVector.push_back({ 0, 0, 1, 1, 2, 2 });
		checkGameVector.push_back({ 2, 0, 2, 1, 2, 2 });
		checkGameVector.push_back({ 2, 0, 1, 0, 0, 0 });
		checkGameVector.push_back({ 2, 0, 1, 1, 0, 2 });
		checkGameVector.push_back({ 0, 1, 1, 1, 2, 1 });
		checkGameVector.push_back({ 1, 2, 1, 1, 1, 0 });
		checkGameVector.push_back({ 2, 1, 1, 1, 0, 1 });
		checkGameVector.push_back({ 1, 0, 1, 1, 1, 2 });
		checkGameVector.push_back({ 0, 1, 2, 1, 1, 1 });
		checkGameVector.push_back({ 1, 2, 1, 0, 1, 1 });
		checkGameVector.push_back({ 0, 2, 2, 0, 1, 1 });
		checkGameVector.push_back({ 2, 2, 0, 0, 1, 1 });
		checkGameVector.push_back({ 0, 2, 2, 2, 1, 2 });
		checkGameVector.push_back({ 0, 0, 2, 0, 1, 0 });
		checkGameVector.push_back({ 0, 2, 0, 0, 0, 1 });
		checkGameVector.push_back({ 2, 2, 2, 0, 2, 1 });
	}

	void AI::PlacePiece(int(*gridArray)[3][3], sf::Sprite gridPieces[3][3], int *gameState)
	{
		try
		{
			// Checks if AI can win.
			for (int i = 0; i < checkGameVector.size(); i++)
			{
				CheckSection(checkGameVector[i][0], checkGameVector[i][1], checkGameVector[i][2], checkGameVector[i][3], checkGameVector[i][4], checkGameVector[i][5], AI_PIECE, gridArray, gridPieces);
			}

			// Checks if Player can win.
			for (int i = 0; i < checkGameVector.size(); i++)
			{
				CheckSection(checkGameVector[i][0], checkGameVector[i][1], checkGameVector[i][2], checkGameVector[i][3], checkGameVector[i][4], checkGameVector[i][5], PLAYER_PIECE, gridArray, gridPieces);
			}

			// Checks if a center is empty.
			CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);

			// Checks if a corner is empty.
			CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);

			// Checks for any other empty piece.
			CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
			CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
			CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);
		}

		catch (int error)
		{

		}

		*gameState = STATE_PLAYING;
	}

	void AI::CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3])
	{
		// Checks if two pieces match.
		if (pieceToCheck == (*gridArray)[x1][y1] && pieceToCheck == (*gridArray)[x2][y2])
		{
			if ((*gridArray)[X][Y] == EMPTY_PIECE)
			{
				(*gridArray)[X][Y] = AI_PIECE;

				gridPieces[X][Y].setTexture(_data->asset.GetTexture("O Piece"));

				gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));

				throw -1;
			}
		}
	}

	void AI::CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], sf::Sprite gridPieces[3][3])
	{
		// Checks if a piece is empty.
		if ((*gridArray)[X][Y] == EMPTY_PIECE)
		{
			(*gridArray)[X][Y] = AI_PIECE;

			gridPieces[X][Y].setTexture(_data->asset.GetTexture("O Piece"));

			gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));

			throw -2;
		}
	}
}