#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "player_class.h"
#include "tetrisBoard_class.h"
#include "tetrisGame_class.h"
#include "tetromino_class.h"
#include "general.h"

using namespace std;

int main()
{
    TetrisGame game;

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Set the console text attribute to the default color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TetrisBoard::COLORS[0]);

    while (true)
    {
        // Print the main menu and get the user's choice
        game.printMenu();
        int choice = _getch();

        // Process the user's choice
        switch (choice)
        {
        case '1':
            // Start a new game without colored blocks and
            // Reset player values for a new game
            game.resetPlayerValues(game);
            game.setColoredGame(false);
            game.settingGameSpeedOption();
            game.gameLoop(game);
            break;

        case '2':
            // Start a new game with colored blocks
            game.resetPlayerValues(game);
            game.settingGameSpeedOption();
            game.setColoredGame(true);
            game.gameLoop(game);
            break;

        case '3':
            // Continue a paused game if the game is paused
            if (game.getGamePaused())
            {
                game.setGamePaused(false);
                game.gameLoop(game);
            }
            break;

        case '8':
            // Display game instructions
            game.showInstructions();
            break;

        case '9':
            // Exit the game
            cout << "Exiting the game. Goodbye!" << endl;
            return 0;  // Terminate the program

        default:
            // Invalid choice
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
