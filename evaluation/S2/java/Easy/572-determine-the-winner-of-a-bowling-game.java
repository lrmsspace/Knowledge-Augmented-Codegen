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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Oriented area of a triangle (geometry, number, simulation)
//   • When to use: Use when determining the orientation of three 2D points (clockwise, counterclockwise, or collinear) or calculating the signed area of a triangle formed by them. It's crucial for geometric algorithms like convex hull construction and point-in-polygon tests.
//   • Idea: Calculates the signed area of a triangle defined by three 2D points, indicating their orientation relative to each other. A positive sign typically means counterclockwise, negative means clockwise, and zero indicates collinearity.
//   • Invariants: The sign of the result correctly indicates the orientation of p1, p2, p3 (e.g., positive for counter-clockwise).; If the points are collinear, the calculated oriented area is exactly zero.
//   • Tips: The sign of the result directly indicates the orientation of the points.; The absolute value of the result gives the standard unsigned area of the triangle.
//   • Pitfalls: Floating-point precision issues can lead to incorrect collinearity checks or orientation.; Inconsistent definitions of 'clockwise' vs. 'counterclockwise' can flip the sign interpretation.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
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
            if (i > 0 && player1[i - 1] == 10) {
                score1 += player1[i];
            }
            if (i > 1 && player1[i - 2] == 10) {
                score1 += player1[i];
            }
            if (i > 0 && player2[i - 1] == 10) {
                score2 += player2[i];
            }
            if (i > 1 && player2[i - 2] == 10) {
                score2 += player2[i];
            }
        }
        return Integer.compare(score1, score2);         
    }
}
