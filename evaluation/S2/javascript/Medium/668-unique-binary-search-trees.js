// Source: https://leetcode.com/problems/unique-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
//
// Example:
// Input: n = 3
// Output: 5
//
// Constraints:
// 1 <= n <= 19
//
// Helpful references (internal KB):
// - Catalan Numbers (number, array, recursion, dp-1d, counting)
//   • When to use: Use when counting specific combinatorial objects that exhibit a recursive structure, such as balanced parentheses, binary trees, or non-crossing partitions. It applies to problems where items can be split into two independent subproblems.
//   • Idea: Catalan numbers are a sequence of natural numbers appearing in various combinatorial problems, often involving recursively defined objects. They are computed via a recurrence relation or a direct formula, typically achieving O(N^2) with DP or O(N) for the direct formula.
//   • Invariants: C[0] is initialized to 1, representing the base case for an empty sequence.; For any k > 0, C[k] stores the k-th Catalan number.
//   • Tips: Recognize the underlying recursive structure that splits a problem into two smaller, independent subproblems.; Memorize the first few Catalan numbers (1, 1, 2, 5, 14, 42, 132) to quickly identify the pattern.
//   • Pitfalls: Forgetting the base case C(0) = 1, which is crucial for the recurrence relation.; Integer overflow when using the direct factorial formula for large N; modular arithmetic or large number libraries may be required.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use when counting labeled trees or converting between a labeled tree and a unique sequence representation for combinatorial analysis. It provides a bijection for problems involving N labeled nodes.
//   • Idea: Prüfer code is a unique sequence of length N-2 that represents a labeled tree with N nodes. It is constructed by iteratively removing the smallest-labeled leaf and recording its neighbor, and can be reconstructed back into the tree.
//   • Invariants: The Prüfer sequence always contains N-2 elements for a tree with N nodes.; At each step of encoding, the removed node is a leaf with the smallest label among all current leaves.
//   • Tips: Maintain an array of node degrees for efficient updates.; Use a min-priority queue to quickly find the smallest-labeled leaf.
//   • Pitfalls: Incorrectly updating node degrees after removal.; Off-by-one errors when dealing with 0-indexed vs. 1-indexed labels.
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
var numTrees = function(n) {
    const dp = Array(n + 1).fill(0);
    dp[0] = 1;
    for (let i = 1; i <= n; i++) {
        for (let j = 1; j <= i; j++) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    return dp[n];
};
