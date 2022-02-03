// SnekGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "Game.h"
#include <thread>

/// <summary>
/// The FPS of the snake game
/// </summary>
const float g_fps{ 30.0f };

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
    /*system("cls");*/
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

void play() {
    // Create the game field
    Game game{ 20, 20 };

    std::thread getKeyPressed{ handleKeyInput, std::ref(game) };

    while (game.isActive) {
        clearScreen();
        game.update();
        if (!game.isActive)
            break;
        Sleep((int)(1000.0 / g_fps));
    }

    getKeyPressed.join();
    std::cout << "You died with a length of " << game.getSnake().m_length - 1 << "!" << std::endl;
    Sleep(1000);
    std::cout << "Press 'W' to Play and 'S' to Quit.";
}

int main()
{
    // Wait for player input to begin the game
    std::cout << "Press 'W' to Play and 'S' to Quit.";
    while (true) {
        if (GetAsyncKeyState('W') & 0x8000)
            play();
        else if (GetAsyncKeyState('S') & 0x8000)
            return 1;
    }
    
    return 1;
}
