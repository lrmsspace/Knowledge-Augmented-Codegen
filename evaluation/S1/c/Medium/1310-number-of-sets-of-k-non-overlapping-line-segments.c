// Source: https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/   |   Difficulty: Medium
//
// Problem Description:
// Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments such that each segment covers two or more points. The endpoints of each segment must have integral coordinates. The k line segments do not have to cover all n points, and they are allowed to share endpoints.
//
// Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.
//
// Example:
// Input: n = 4, k = 2
// Output: 5
// Explanation: The two line segments are shown in red and blue.
// The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= k <= n-1
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfSets(int n, int k) {
    const int MOD = 1000000007;
    // We need to choose 2k endpoints from (n - 1) possible gaps between n points
    // The number of ways to choose 2k endpoints from (n - 1) gaps is C(n - 1, 2k)
    // This is equivalent to C(n - 1, n - 1 - 2k) = C(n - 1, n - 2k - 1)
    // We can use a combinatorial formula to compute this efficiently

    if (2 * k > n - 1) {
        return 0; // Not enough gaps to place k segments
    }

    long long numerator = 1;
    long long denominator = 1;

    for (int i = 0; i < 2 * k; i++) {
        numerator = (numerator * (n - 1 - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }

    // Fermat's Little Theorem for modular inverse
    long long denominator_inv = 1;
    int power = MOD - 2; // MOD is prime
    long long base = denominator;

    while (power) {
        if (power % 2) {
            denominator_inv = (denominator_inv * base) % MOD;
        }
        base = (base * base) % MOD;
        power /= 2;
    }

    return (numerator * denominator_inv) % MOD;     
}
