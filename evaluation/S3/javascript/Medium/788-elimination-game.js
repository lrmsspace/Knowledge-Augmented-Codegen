// Source: https://leetcode.com/problems/elimination-game/   |   Difficulty: Medium
//
// Problem Description:
// You have a list arr of all integers in the range [1, n] sorted in a strictly increasing order. Apply the following algorithm on arr:
//
//
// 	Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
// 	Repeat the previous step again, but this time from right to left, remove the rightmost number and every other number from the remaining numbers.
// 	Keep repeating the steps again, alternating left to right and right to left, until a single number remains.
//
//
// Given the integer n, return the last number that remains in arr.
//
// Example:
// Input: n = 9
// Output: 6
// Explanation:
// arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
// arr = [2, 4, 6, 8]
// arr = [2, 6]
// arr = [6]
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {number}
 */
var lastRemaining = function(n) {
    let head = 1; // The first number in the current list
    let step = 1; // The step size (distance between remaining numbers)
    let remaining = n; // The count of remaining numbers
    let leftToRight = true; // Direction of elimination

    while (remaining > 1) {
        // If we're moving left to right, or if we're moving right to left and the remaining count is odd,
        // the head will move forward by the current step size
        if (leftToRight || remaining % 2 === 1) {
            head += step;
        }

        // Double the step size for the next round since every other number is removed
        step *= 2;
        // Halve the remaining count since half of the numbers are removed each round
        remaining = Math.floor(remaining / 2);
        // Alternate the direction of elimination
        leftToRight = !leftToRight;
    }

    return head;
};
