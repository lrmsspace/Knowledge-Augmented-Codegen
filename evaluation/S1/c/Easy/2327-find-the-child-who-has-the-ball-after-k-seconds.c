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
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfChild(int n, int k) {
    int cycle = 2 * (n - 1);
    int position = k % cycle;
    if (position < n) {
        return position;
    } else {
        return cycle - position;
    }       
}
