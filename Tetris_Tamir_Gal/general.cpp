#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
using namespace std;

// Function to move the cursor to the specified coordinates on the console
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;

    cout.flush();  // Flush the output buffer
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// Function to clear the console screen
void clrscr()
{
    system("cls");
}
