#include "tetrisGame_class.h"
#include"tetrisBoard_class.h"
#include"tetromino_class.h"
#include "general.h"
#include <cstdlib>  // Include for rand() function
#include <conio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

// Function to get a reference to the player based on the given index
Player& TetrisGame::getPlayer(int index, TetrisGame& game)
{
	if (index == 1)
		return game.player1;
	else
		return game.player2;
}

// Function to draw the Tetromino on the game board
void TetrisGame::drawTetromino(Tetromino& p, TetrisBoard& board)
{
	int shapeX = p.getX();
	int shapeY = p.getY();
	int backColor;

	// Choose the background color based on the game settings
	if (this->getColoredGame())
		backColor = p.getBackgroundcolor();
	else
		backColor = TetrisBoard::COLORS[0];

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backColor);

	// Iterate through the Tetromino shape and draw it on the board
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Print spaces for empty cells and '#' for filled cells
			if (p.getCurrentShapeChar(i,j) != ' ')
			{
				gotoxy((shapeX + j), shapeY + i);
				cout << '#';
			}
		}
	}
}

// Function to handle player input and move Tetrominos accordingly
void TetrisGame::moveTetrominoWithInput(Player& player1, Player& player2, int gameSpeed)
{
	// Retrieve the Tetrominos for each player
	Tetromino player1Tetromino = player1.getPlayerTetromino();
	Tetromino player2Tetromino = player2.getPlayerTetromino();

	// Continue the game loop until one of the players loses
	while (player1.checkIfLost() == false && player2.checkIfLost() == false)
	{
		// Retrieve the game boards for each player
		TetrisBoard player1Board = player1.getPlayerBoard();
		TetrisBoard player2Board = player2.getPlayerBoard();

		// Redraw the Tetris board borders for both players
		player1Board.drawBoard(TetrisBoard::LEFT_PLAYER1_BORDER, TetrisBoard::MIN_Y);
		player2Board.drawBoard(TetrisBoard::LEFT_PLAYER2_BORDER, TetrisBoard::MIN_Y);

		// Print player scores above their respective sides
		player1Board.printPlayerScore(player1);
		player2Board.printPlayerScore(player2);

		int keyPressed = 0;

		// Check for key presses
		if (_kbhit())
		{
			// Get the pressed key
			int keyPressed = _getch();

			// Adjust the key for character conversions
			if (keyPressed >= 'a' && keyPressed != ESCAPE)
				keyPressed -= CHARACTERS_OFFSET;

			// Check for the ESC key to pause the game
			if (keyPressed == (int)Tetromino::ePlayersKeys::ESC)
			{
				this->setGamePaused(true);
				return;
			}

			// Process input for Player 1
			if (keyPressed == (int)Tetromino::ePlayersKeys::PLAYER_1_LEFT || keyPressed == (int)Tetromino::ePlayersKeys::PLAYER_1_RIGHT || keyPressed == (int)Tetromino::ePlayersKeys::PLAYER_1_ROTATE_CLOCKWISE || keyPressed == (int)Tetromino::ePlayersKeys::PLAYER_1_DROP || keyPressed == (int)Tetromino::ePlayersKeys::PLAYER_1_ROTATE_COUNTERCLOCKWISE)
			{
				// Apply the Tetromino move based on the key press
				player1Tetromino.applyTetrominoMove((Tetromino::ePlayersKeys)keyPressed, player1);

				// Check if a new Tetromino is needed for Player 1
				if (player1.checkIfNewTetrominoNeeded() && player1.checkIfLost() == false)
				{
					clearPendingKeys();
					player1Tetromino = player1Board.generateRandomTetromino(1);
					player1.setPlayerTetromino(player1Tetromino);
					player1.setisNewTetrominoNeeded(false);
				}
			}
			// Process input for Player 2
			else
			{
				player2Tetromino.applyTetrominoMove((Tetromino::ePlayersKeys)keyPressed, player2);

				if (player2.checkIfNewTetrominoNeeded() && player2.checkIfLost() == false)
				{
					clearPendingKeys();
					player2Tetromino = player2Board.generateRandomTetromino(2);
					player2.setPlayerTetromino(player2Tetromino);
					player2.setisNewTetrominoNeeded(false);
				}
			}
		}

		// Draw Tetrominos on the boards
		drawTetromino(player1Tetromino, player1Board);
		drawTetromino(player2Tetromino, player2Board);

		Sleep(gameSpeed);  // Adjust the sleep duration for the desired speed

		// Move Tetrominos down
		player1Tetromino.applyTetrominoMove((Tetromino::ePlayersKeys)DOWN, player1);
		if (player1.checkIfNewTetrominoNeeded() && player1.checkIfLost() == false)
		{
			clearPendingKeys();
			player1Tetromino = player1Board.generateRandomTetromino(1);
			player1.setPlayerTetromino(player1Tetromino);
			player1.setisNewTetrominoNeeded(false);
		}

		player2Tetromino.applyTetrominoMove((Tetromino::ePlayersKeys)DOWN, player2);
		if (player2.checkIfNewTetrominoNeeded() && player2.checkIfLost() == false)
		{
			player2Tetromino = player2Board.generateRandomTetromino(2);
			player2.setPlayerTetromino(player2Tetromino);
			player2.setisNewTetrominoNeeded(false);
		}

		// Update Tetrominos after movement
		player1Tetromino = player1.getPlayerTetromino();
		player2Tetromino = player2.getPlayerTetromino();

		clrscr();  // Clear the screen before drawing in the new position
	}
}

// Main game loop
void TetrisGame::gameLoop(TetrisGame& game)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);

	// Create Tetrominos for both players
	Tetromino tetromino1, tetromino2;

	// Get references to player objects
	Player& player1 = game.getPlayer(1, game);
	Player& player2 = game.getPlayer(2, game);

	// Get player boards
	TetrisBoard player1Board = player1.getPlayerBoard();
	TetrisBoard player2Board = player2.getPlayerBoard();

	// Set player indices
	player1.setIdx(1);
	player2.setIdx(2);

	// Generate initial Tetrominos for both players
	tetromino1 = player1Board.generateRandomTetromino(1);
	tetromino2 = player2Board.generateRandomTetromino(2);

	// Set initial Tetrominos for players
	player1.setPlayerTetromino(tetromino1);
	player2.setPlayerTetromino(tetromino2);

	// Start the game loop
	game.moveTetrominoWithInput(player1, player2 ,game.getGameSpeed());

	// Check if the game is paused
	if (game.getGamePaused() == true)
		return;

	// Clear the screen
	clrscr();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);

	// Clear pending keys
	game.clearPendingKeys();


	/// make decision when both players lose at the exact same time
	//the player with higher score would win and it may be a tie only if both lose and there is also tie in the score.
	if (player1.checkIfLost() && player2.checkIfLost())
	{
		if (player1.getScore() > player2.getScore())
			cout << "Player 1 Won!" << endl << "Score: " << player1.getScore() << endl << endl;
		else if (player1.getScore() < player2.getScore())
			cout << "Player 2 Won!" << endl << "Score: " << player2.getScore() << endl << endl;
		else
			cout << "Its a tie Game!";

	}
	else
	{
		// Display the winner and scores
		if (player1.checkIfLost())
			cout << "Player 2 Won!" << endl << "Score: " << player2.getScore() << endl << endl;
		else
			cout << "Player 1 Won!" << endl << "Score: " << player1.getScore() << endl << endl;
	}

	// Prompt user to return to menu
	cout << "Press any key to return to menu..." << endl;
	_getch();

	
}

// Function to reset player values for a new game
void TetrisGame::resetPlayerValues(TetrisGame& game)
{
	Player& player1 = game.getPlayer(1, game);
	Player& player2 = game.getPlayer(2, game);
	TetrisBoard& player1Board = player1.getPlayerBoard();
	TetrisBoard& player2Board = player2.getPlayerBoard();

	// Reset player attributes
	player1.setIsLost(false);
	player1.setScore(0);
	player1.setisNewTetrominoNeeded(false);

	player2.setIsLost(false);
	player2.setScore(0);
	player2.setisNewTetrominoNeeded(false);

	// Reset player boards
	player1.resetBoard(player1Board);
	player2.resetBoard(player2Board);
}

// Function to display game instructions
void TetrisGame::showInstructions()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);
	clrscr();

	// Display control instructions
	cout << "Instructions:" << endl << endl;
	cout << "Left Player Controls:" << endl;
	cout << "  LEFT: a or A" << endl;
	cout << "  RIGHT: d or D" << endl;
	cout << "  ROTATE clockwise: s or S" << endl;
	cout << "  ROTATE counterclockwise: w or W" << endl;
	cout << "  DROP: x or X" << endl << endl;

	cout << "Right Player Controls:" << endl;
	cout << "  LEFT: j or J" << endl;
	cout << "  RIGHT: l (small L) or L" << endl;
	cout << "  ROTATE clockwise: k or K" << endl;
	cout << "  ROTATE counterclockwise: i or I (uppercase i)" << endl;
	cout << "  DROP: m or M" << endl << endl;

	// Prompt user to return to the main menu
	cout << "Press any key to return to the main menu...";
	_getch();
}

// Function to print the main menu
void TetrisGame::printMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);
	clrscr();

	// Display main menu options
	cout << "Main Menu:" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(2) Start a new game with colors" << endl;

	// Display the option to continue a paused game if applicable
	if (this->gamePaused == true)
		cout << "(3) Continue a paused game" << endl;

	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

//Function to get the game speed preferred by the user
void TetrisGame::settingGameSpeedOption()
{
	clrscr();

	// Display speed menu options
	cout << "Speed Menu:" << endl;
	cout << "(1) Slow paced game" << endl;
	cout << "(2) Medium paced game" << endl;
	cout << "(3) Fast paced game" << endl;

	int choice = _getch();

	// Process the user's choice
	switch (choice)
	{
	case '1':
		this->setGameSpeed(SLOW);
		break;

	case '2':
		this->setGameSpeed(MEDIUM);
		break;

	case '3':

		this->setGameSpeed(FAST);
		break;
	}

}

// Function to clear any pending keys in the input buffer
void TetrisGame::clearPendingKeys()
{
	while (_kbhit())
	{
		_getch(); // Consume and discard the key press
	}
}
