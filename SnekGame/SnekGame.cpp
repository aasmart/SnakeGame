// SnekGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "Game.h"
#include <thread>
#include <map>

/// <summary>
/// The FPS of the snake game
/// </summary>
const float g_fps{ 60.0f };
std::random_device dev;

void play() {
    while (true) {
        std::mt19937 rng{ dev() };
        // Create the game field
        Game game{ 15, 15, rng };

        while (game.isActive) {
            if (GetAsyncKeyState('Z') & 0x8000)
                return;

            game.update();
            if (!game.isActive)
                break;
            Sleep((int)(1000.0 / g_fps));
        }
    }
}

int main()
{

    // Wait for player input to begin the game
    std::cout << "Press 'W' to Play and 'Z' to Quit.";
    while (true) {
        if (GetAsyncKeyState('W') & 0x8000)
            play();
        else if (GetAsyncKeyState('Z') & 0x8000)
            return 0;
    }
    
    return 0;
}
