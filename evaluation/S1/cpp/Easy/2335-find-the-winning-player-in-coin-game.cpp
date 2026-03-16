// Source: https://leetcode.com/problems/find-the-winning-player-in-coin-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers x and y, denoting the number of coins with values 75 and 10 respectively.
//
// Alice and Bob are playing a game. Each turn, starting with Alice, the player must pick up coins with a total value 115. If the player is unable to do so, they lose the game.
//
// Return the name of the player who wins the game if both players play optimally.
//
// Example:
// Input: x = 2, y = 7
//
// Output: "Alice"
//
// Explanation:
//
// The game ends in a single turn:
//
//
// 	Alice picks 1 coin with a value of 75 and 4 coins with a value of 10.
//
// Constraints:
// 1 <= x, y <= 100
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string winningPlayer(int x, int y) {
        // Each player needs to pick coins worth 115 each turn.
        // The only combinations to make 115 are:
        // 1. One 75-coin and four 10-coins (1x75 + 4x10 = 115)
        // 2. Eleven 10-coins (11x10 = 110)
        //
        // The first option is more efficient in terms of the number of coins used.
        // Therefore, both players will prefer to use the first option as long as possible.
        //
        // The game will continue until one player cannot make a valid move.
        // This will happen when there are not enough coins left to make a total of 115.
        //
        // Let's analyze the maximum number of turns possible:
        // - Each turn using the first option consumes 1x75-coin and 4x10-coins.
        // - The maximum number of turns that can be played using the first option is limited by the smaller of x (number of 75-coins) and y/4 (number of sets of four 10-coins).
        //
        // After using the first option as much as possible, if there are still enough 10-coins left, players can use the second option (11x10-coins).
        //
        // The game ends when a player cannot make a valid move.

        int maxTurnsUsingFirstOption = min(x, y / 4);
        x -= maxTurnsUsingFirstOption;
        y -= maxTurnsUsingFirstOption * 4;

        int totalTurns = maxTurnsUsingFirstOption;

        // Now check how many additional turns can be played using only 10-coins
        totalTurns += y / 11;

        // If totalTurns is odd, Alice wins (she starts first), otherwise Bob wins
        return (totalTurns % 2 == 1) ? "Alice" : "Bob";         
    }
};
