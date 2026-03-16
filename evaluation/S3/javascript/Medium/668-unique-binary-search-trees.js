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
// - Catalan Numbers (number, counting)
//   • When to use: Use when counting arrangements of objects that follow a specific non-crossing or balancing rule, often involving recursive decomposition or paths constrained by a diagonal.
//   • Idea: Catalan numbers count the number of ways to arrange certain combinatorial objects, such as balanced parentheses sequences or monotonic paths that do not cross a diagonal. They can be computed using a recurrence relation (O(N^2) with DP) or a direct binomial coefficient formula (O(N) or O(N log N)).
//   • Invariants: dp[i] stores the i-th Catalan number, correctly computed from dp[0] through dp[i-1].; For each n, the sum sum(dp[k] * dp[n-1-k]) iterates through all valid partitions of the problem.
//   • Tips: Memoize the recursive solution to avoid redundant computations, transforming it into dynamic programming.; For large N, use modular arithmetic if results are required modulo a prime to prevent integer overflow.
//   • Pitfalls: Forgetting to correctly handle the base cases, typically C0 = 1 and C1 = 1.; Encountering integer overflow when calculating large binomial coefficients without appropriate modular arithmetic.
// - Binomial Coefficients (number, enumeration)
//   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
//   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
//   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
//   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
//   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
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
    const dp = new Array(n + 1).fill(0);
    dp[0] = 1; // Base case: There is one unique BST for an empty tree

    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j]; // C(i) += C(j) * C(i-1-j)
        }
    }

    return dp[n];
};
