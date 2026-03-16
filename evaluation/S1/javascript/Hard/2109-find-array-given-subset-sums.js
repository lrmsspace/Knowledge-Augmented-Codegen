// Source: https://leetcode.com/problems/find-array-given-subset-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).
//
// Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
//
// An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.
//
// Note: Test cases are generated such that there will always be at least one correct answer.
//
// Example:
// Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
// Output: [1,2,-3]
// Explanation: [1,2,-3] is able to achieve the given subset sums:
// - []: sum is 0
// - [1]: sum is 1
// - [2]: sum is 2
// - [1,2]: sum is 3
// - [-3]: sum is -3
// - [1,-3]: sum is -2
// - [2,-3]: sum is -1
// - [1,2,-3]: sum is 0
// Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
//
// Constraints:
// 1 <= n <= 15
// 	sums.length == 2n
// 	-104 <= sums[i] <= 104
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} sums
 * @return {number[]}
 */
var recoverArray = function(n, sums) {
    sums.sort((a, b) => a - b);
    const ans = new Array(n);

    for (let i = 0; i < n; i++) {
        const diff = sums[1] - sums[0];
        ans[i] = diff;

        const countMap = new Map();
        for (const sum of sums) {
            countMap.set(sum, (countMap.get(sum) || 0) + 1);
        }

        const newSums = [];
        for (const sum of sums) {
            if (countMap.get(sum) > 0) {
                newSums.push(sum);
                countMap.set(sum, countMap.get(sum) - 1);
                countMap.set(sum + diff, (countMap.get(sum + diff) || 0) - 1);
            }
        }
        sums = newSums;
    }

    return ans;
};
