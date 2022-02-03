// SnekGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "Game.h"
#include <thread>

/// <summary>
/// The FPS of the snake game
/// </summary>
const float g_fps{ 20.0f };

/// <summary>
/// Clears the screen
/// </summary>
/// <param name="fill">The character to fill the screen with. Defaults to an empty character</param>
void clearScreen(char fill = ' ') {
    // https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648    
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

/// <summary>
/// Determine which of the keys the player is pressing (W, A, S, D)
/// </summary>
/// <returns>The direction the pressed key corresponds to</returns>
Direction getKey() {
    if (GetAsyncKeyState('W') & 0x8000) {
        return Direction::UP;
    }
    else if (GetAsyncKeyState('S') & 0x8000) {
        return Direction::DOWN;
    }
    else if (GetAsyncKeyState('A') & 0x8000) {
        return Direction::LEFT;
    }
    else if (GetAsyncKeyState('D') & 0x8000) {
        return Direction::RIGHT;
    }
    else {
        return Direction::NONE;
    }
}

/// <summary>
/// While the given game is active, get the players key presses and set the snake's direction
/// to the corresponding direction
/// </summary>
/// <param name="game">The current game</param>
void handleKeyInput(Game& game) {
    while (game.isActive) {
        game.getSnake().setDirection(getKey());
    }
}

int main()
{
    // Wait for player input to begin the game
    std::cout << "Press 'W' to Start and 'S' to Cancel";
    while (true) {
        if (GetAsyncKeyState('W') & 0x8000)
            break;
        else if (GetAsyncKeyState('S') & 0x8000)
            return 1;
    }

    // Create the game field
    Game game{20, 20};

    std::thread getKeyPressed{handleKeyInput, std::ref(game)};

    while (game.isActive) {
        clearScreen();
        game.update();
        if (!game.isActive)
            break;
        Sleep((int)(1000.0 / g_fps));
    }

    getKeyPressed.join();
    std::cout << "You died with a length of " << game.getSnake().m_length - 1 << "!";
    return 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
