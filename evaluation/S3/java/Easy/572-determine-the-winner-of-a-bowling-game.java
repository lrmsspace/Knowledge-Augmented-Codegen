// Source: https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed integer arrays player1 and player2, representing the number of pins that player 1 and player 2 hit in a bowling game, respectively.
//
// The bowling game consists of n turns, and the number of pins in each turn is exactly 10.
//
// Assume a player hits xi pins in the ith turn. The value of the ith turn for the player is:
//
//
// 	2xi if the player hits 10 pins in either (i - 1)th or (i - 2)th turn.
// 	Otherwise, it is xi.
//
//
// The score of the player is the sum of the values of their n turns.
//
// Return
//
//
// 	1 if the score of player 1 is more than the score of player 2,
// 	2 if the score of player 2 is more than the score of player 1, and
// 	0 in case of a draw.
//
// Example:
// Input: player1 = [5,10,3,2], player2 = [6,5,7,3]
//
// Output: 1
//
// Explanation:
//
// The score of player 1 is 5 + 10 + 2*3 + 2*2 = 25.
//
// The score of player 2 is 6 + 5 + 7 + 3 = 21.
//
// Constraints:
// n == player1.length == player2.length
// 	1 <= n <= 1000
// 	0 <= player1[i], player2[i] <= 10
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int isWinner(int[] player1, int[] player2) {
        int score1 = 0, score2 = 0;
        for (int i = 0; i < player1.length; i++) {
            score1 += player1[i];
            score2 += player2[i];
            if (i > 0) {
                if (player1[i - 1] == 10) {
                    score1 += player1[i];
                }
                if (player2[i - 1] == 10) {
                    score2 += player2[i];
                }
            }
            if (i > 1) {
                if (player1[i - 2] == 10) {
                    score1 += player1[i];
                }
                if (player2[i - 2] == 10) {
                    score2 += player2[i];
                }
            }
        }
        return Integer.compare(score1, score2);         
    }
}
