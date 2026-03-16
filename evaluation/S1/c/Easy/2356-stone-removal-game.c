// Source: https://leetcode.com/problems/stone-removal-game/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.
//
//
// 	Alice starts by removing exactly 10 stones on her first turn.
// 	For each subsequent turn, each player removes exactly 1 fewer stone than the previous opponent.
//
//
// The player who cannot make a move loses the game.
//
// Given a positive integer n, return true if Alice wins the game and false otherwise.
//
// Example:
// Input: n = 12
//
// Output: true
//
// Explanation:
//
//
// 	Alice removes 10 stones on her first turn, leaving 2 stones for Bob.
// 	Bob cannot remove 9 stones, so Alice wins.
//
// Constraints:
// 1 <= n <= 50
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canAliceWin(int n) {
    // Alice can only win if there are at least 10 stones to remove on her first turn
    return n >= 10;     
}
