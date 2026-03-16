// Source: https://leetcode.com/problems/find-the-child-who-has-the-ball-after-k-seconds/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers n and k. There are n children numbered from 0 to n - 1 standing in a queue in order from left to right.
//
// Initially, child 0 holds a ball and the direction of passing the ball is towards the right direction. After each second, the child holding the ball passes it to the child next to them. Once the ball reaches either end of the line, i.e. child 0 or child n - 1, the direction of passing is reversed.
//
// Return the number of the child who receives the ball after k seconds.
//
// Example:
// Input: n = 3, k = 5
//
// Output: 1
//
// Explanation:
//
//
// 	
// 		
// 			Time elapsed
// 			Children
// 		
// 		
// 			0
// 			[0, 1, 2]
// 		
// 		
// 			1
// 			[0, 1, 2]
// 		
// 		
// 			2
// 			[0, 1, 2]
// 		
// 		
// 			3
// 			[0, 1, 2]
// 		
// 		
// 			4
// 			[0, 1, 2]
// 		
// 		
// 			5
// 			[0, 1, 2]
//
// Constraints:
// 2 <= n <= 50
// 	1 <= k <= 50
//
//
//  
// Note: This question is the same as  2582: Pass the Pillow.
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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numberOfChild(int n, int k) {
        // The ball moves in a back-and-forth pattern. The total number of positions the ball can take before it starts repeating is 2 * (n - 1).
        // We can use modulo to find the effective position of the ball after k seconds.
        int cycleLength = 2 * (n - 1);
        int position = k % cycleLength;

        // If the position is less than n, it means the ball is moving to the right.
        // Otherwise, it's moving to the left, and we need to calculate the position accordingly.
        if (position < n) {
            return position; // Moving to the right
        } else {
            return cycleLength - position; // Moving to the left
        }           
    }
}
