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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String winningPlayer(int x, int y) {
        int totalValue = x * 75 + y * 10;
        int turns = totalValue / 115;
        return (turns % 2 == 1) ? "Alice" : "Bob";          
    }
}
