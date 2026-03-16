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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean canAliceWin(int n) {
        return n >= 10;         
    }
}
