#ifndef TETROMINO_H
#define TETROMINO_H

#include <windows.h>

// Forward declaration of TetrisBoard and Player
class TetrisBoard;
class Player;

class Tetromino
{
private:
    // Tetromino shapes
    static const char shapes[7][4][4];  // Static array

    int backgroundColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    int x;  // X-coordinate of the Tetromino
    int y;  // Y-coordinate of the Tetromino
    int shapeIndex;  // Index representing the current shape of the Tetromino
    char currentShape[4][4];
   
public:

    enum class ePlayersKeys {
        PLAYER_1_LEFT = 'A', PLAYER_1_RIGHT = 'D', PLAYER_1_ROTATE_CLOCKWISE = 'S', PLAYER_1_ROTATE_COUNTERCLOCKWISE = 'W', PLAYER_1_DROP = 'X', ESC = 27,
        PLAYER_2_LEFT = 'J', PLAYER_2_RIGHT = 'L', PLAYER_2_ROTATE_CLOCKWISE = 'K', PLAYER_2_ROTATE_COUNTERCLOCKWISE = 'I', PLAYER_2_DROP = 'M'
    };


    // Constructor
    Tetromino(int shapeIndex = 0, int player = 1);  // Default value for shapeIndex

    // Methods

    // Rotate the Tetromino clockwise
    void rotateClockwise();

    // Rotate the Tetromino counterclockwise
    void rotateCounterclockwise();

    // Getter methods
    int getX() const { return x; }
    int getY() const { return y; }
    int getShapeIndex() const { return shapeIndex; }
    char getCurrentShapeChar(int i, int j) const { return currentShape[i][j]; }

    // Setter methods
    void setX(int newX);
    void setY(int newY);
    void applyTetrominoMove(Tetromino::ePlayersKeys key, Player& player);
    void setCurrentShapeChar(int i, int j, const char  symbol) { this->currentShape[i][j] = symbol; }

    // Set the background color of the Tetromino
    void setBackgroundcolor(int color) { backgroundColor = color; }

    // Get the background color of the Tetromino
    int getBackgroundcolor() const { return backgroundColor; }

};

#endif // TETROMINO_H
