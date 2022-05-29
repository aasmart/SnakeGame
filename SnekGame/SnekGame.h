#pragma once

#include <map>
#include <array>

/// <summary>
/// The map for the Q Function. Related game states to actions
/// </summary>
std::map<std::array<int, Game::states>, std::array<float, 3>> Q;

/// <summary>
///  The amount of game iterations the AI has played
/// </summary>
int iterations = 0;

/// <summary>
/// The highest score obtained by the snake
/// </summary>
int highScore = 0;