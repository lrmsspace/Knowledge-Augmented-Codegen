// Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
//
// Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
//
// Example:
// Input: n = 4, k = 6
//
// Output: [3,4,1,2]
//
// Explanation:
//
// The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
//
//
// 	[1, 2, 3, 4]
// 	[1, 4, 3, 2]
// 	[2, 1, 4, 3]
// 	[2, 3, 4, 1]
// 	[3, 2, 1, 4]
// 	[3, 4, 1, 2] ← 6th permutation
// 	[4, 1, 2, 3]
// 	[4, 3, 2, 1]
//
//
// Since k = 6, we return [3, 4, 1, 2].
//
// Constraints:
// 1 <= n <= 100
// 	1 <= k <= 1015
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Catalan Numbers (number, array, recursion, dp-1d, counting)
//   • When to use: Use when counting specific combinatorial objects that exhibit a recursive structure, such as balanced parentheses, binary trees, or non-crossing partitions. It applies to problems where items can be split into two independent subproblems.
//   • Idea: Catalan numbers are a sequence of natural numbers appearing in various combinatorial problems, often involving recursively defined objects. They are computed via a recurrence relation or a direct formula, typically achieving O(N^2) with DP or O(N) for the direct formula.
//   • Invariants: C[0] is initialized to 1, representing the base case for an empty sequence.; For any k > 0, C[k] stores the k-th Catalan number.
//   • Tips: Recognize the underlying recursive structure that splits a problem into two smaller, independent subproblems.; Memorize the first few Catalan numbers (1, 1, 2, 5, 14, 42, 132) to quickly identify the pattern.
//   • Pitfalls: Forgetting the base case C(0) = 1, which is crucial for the recurrence relation.; Integer overflow when using the direct factorial formula for large N; modular arithmetic or large number libraries may be required.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* permute(int n, long long k, int* returnSize) {
    int totalOdds = (n + 1) / 2;
    int totalEvens = n / 2;

    // Precompute Catalan numbers up to max(totalOdds, totalEvens)
    int maxHalf = totalOdds > totalEvens ? totalOdds : totalEvens;
    unsigned long long catalan[101] = {0};
    catalan[0] = 1;
    for (int i = 1; i <= maxHalf; ++i) {
        catalan[i] = catalan[i - 1] * 2 * (2 * i - 1) / (i + 1);
    }

    unsigned long long totalPermutations = catalan[totalOdds] * catalan[totalEvens];
    if (k > totalPermutations) {
        *returnSize = 0;
        return NULL; // k is larger than the number of valid permutations
    }

    int* result = (int*)malloc(n * sizeof(int));
    int oddNums[51], evenNums[51];
    for (int i = 0; i < totalOdds; ++i) oddNums[i] = 2 * i + 1;
    for (int i = 0; i < totalEvens; ++i) evenNums[i] = 2 * (i + 1);

    int oddCount = totalOdds, evenCount = totalEvens;
    for (int i = 0; i < n; ++i) {
        unsigned long long oddWays = (oddCount > 0) ? catalan[oddCount - 1] * catalan[evenCount] : 0;
        if (k <= oddWays && oddCount > 0) {
            result[i] = oddNums[0];
            // Remove used odd number
            for (int j = 0; j < oddCount - 1; ++j) oddNums[j] = oddNums[j + 1];
            oddCount--;
        } else {
            if (oddCount > 0) k -= oddWays;
            result[i] = evenNums[0];
            // Remove used even number
            for (int j = 0; j < evenCount - 1; ++j) evenNums[j] = evenNums[j + 1];
            evenCount--;
        }
    }

    *returnSize = n;     
    return result;   
}
