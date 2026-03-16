// Source: https://leetcode.com/problems/alice-and-bob-playing-flower-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are playing a turn-based game on a field, with two lanes of flowers between them. There are x flowers in the first lane between Alice and Bob, and y flowers in the second lane between them.
//
//
//
// The game proceeds as follows:
//
//
// 	Alice takes the first turn.
// 	In each turn, a player must choose either one of the lane and pick one flower from that side.
// 	At the end of the turn, if there are no flowers left at all in either lane, the current player captures their opponent and wins the game.
//
//
// Given two integers, n and m, the task is to compute the number of possible pairs (x, y) that satisfy the conditions:
//
//
// 	Alice must win the game according to the described rules.
// 	The number of flowers x in the first lane must be in the range [1,n].
// 	The number of flowers y in the second lane must be in the range [1,m].
//
//
// Return the number of possible pairs (x, y) that satisfy the conditions mentioned in the statement.
//
// Example:
// Input: n = 3, m = 2
// Output: 3
// Explanation: The following pairs satisfy conditions described in the statement: (1,2), (3,2), (2,1).
//
// Constraints:
// 1 <= n, m <= 105
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
    public long flowerGame(int n, int m) {
        // Alice wins if the total number of flowers is odd, because she goes first.
        // Therefore, we need to count the pairs (x, y) such that x + y is odd.
        // This happens when one of them is even and the other is odd.

        // Count of even numbers in [1, n]
        long evenCountN = n / 2;
        // Count of odd numbers in [1, n]
        long oddCountN = n - evenCountN;

        // Count of even numbers in [1, m]
        long evenCountM = m / 2;
        // Count of odd numbers in [1, m]
        long oddCountM = m - evenCountM;

        // Pairs where x is even and y is odd
        long pairsEvenXOddY = evenCountN * oddCountM;
        // Pairs where x is odd and y is even
        long pairsOddXEvenY = oddCountN * evenCountM;

        // Total pairs where x + y is odd
        return pairsEvenXOddY + pairsOddXEvenY;         
    }
}
