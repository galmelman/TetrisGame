#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "player_class.h"

class TetrisGame
{
	Player player1, player2;  // Instances of Player for player 1 and player 2
	bool gamePaused = false;   // Flag indicating whether the game is paused
	bool coloredGame = false;  // Flag indicating whether the game is in colored mode
	int gameSpeed;    //option to set the game speed by the user

public:


	static constexpr int ESCAPE = 27; // Esc char ascii value
	static constexpr char DOWN = 'q'; // Char we use to go down one block
	static constexpr char CHARACTERS_OFFSET = ' '; // The offset between the capital letters and the small letters
	static constexpr int  FAST = 300;
	static constexpr int  MEDIUM = 450;
	static constexpr int  SLOW = 600;

	// Getter for the game pause state
	bool getGamePaused() const { return gamePaused; }

	// Setter for the game pause state
	void setGamePaused(bool isPaused) { gamePaused = isPaused; }

	// Getter for the game speed value
	int getGameSpeed() { return gameSpeed; }

	// setter for the game speed value
	void setGameSpeed(int speed) { gameSpeed = speed; }

	// Getter for the colored game state
	bool getColoredGame() const { return coloredGame; }

	// Setter for the colored game state
	void setColoredGame(bool isColored) { coloredGame = isColored; }

	// Move Tetrominos based on player input for player 1 and player 2
	void moveTetrominoWithInput(Player& player1, Player& player2, int gameSpeed);

	void settingGameSpeedOption();

	// Draw a Tetromino on the specified board
	void drawTetromino(Tetromino& tetromino, TetrisBoard& board);

	// Get a reference to the player based on the provided index
	Player& getPlayer(int index, TetrisGame& game);

	// Main game loop
	void gameLoop(TetrisGame& game);

	// Display game instructions
	void showInstructions();

	// Print the main menu
	void printMenu();

	// Reset player values for a new game
	void resetPlayerValues(TetrisGame& game);

	// Clear pending input keys
	void clearPendingKeys();
};

#endif // TETRIS_GAME_H
