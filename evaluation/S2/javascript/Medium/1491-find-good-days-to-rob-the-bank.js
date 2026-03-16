// Source: https://leetcode.com/problems/find-good-days-to-rob-the-bank/   |   Difficulty: Medium
//
// Problem Description:
// You and a gang of thieves are planning on robbing a bank. You are given a 0-indexed integer array security, where security[i] is the number of guards on duty on the ith day. The days are numbered starting from 0. You are also given an integer time.
//
// The ith day is a good day to rob the bank if:
//
//
// 	There are at least time days before and after the ith day,
// 	The number of guards at the bank for the time days before i are non-increasing, and
// 	The number of guards at the bank for the time days after i are non-decreasing.
//
//
// More formally, this means day i is a good day to rob the bank if and only if security[i - time] >= security[i - time + 1] >= ... >= security[i] <= ... <= security[i + time - 1] <= security[i + time].
//
// Return a list of all days (0-indexed) that are good days to rob the bank. The order that the days are returned in does not matter.
//
// Example:
// Input: security = [5,3,3,3,5,6,2], time = 2
// Output: [2,3]
// Explanation:
// On day 2, we have security[0] >= security[1] >= security[2] <= security[3] <= security[4].
// On day 3, we have security[1] >= security[2] >= security[3] <= security[4] <= security[5].
// No other days satisfy this condition, so days 2 and 3 are the only good days to rob the bank.
//
// Constraints:
// 1 <= security.length <= 105
// 	0 <= security[i], time <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} security
 * @param {number} time
 * @return {number[]}
 */
var goodDaysToRobBank = function(security, time) {
    const n = security.length;
    const nonIncreasing = new Array(n).fill(0);
    const nonDecreasing = new Array(n).fill(0);
    
    for (let i = 1; i < n; i++) {
        if (security[i] <= security[i - 1]) {
            nonIncreasing[i] = nonIncreasing[i - 1] + 1;
        }
    }
    
    for (let i = n - 2; i >= 0; i--) {
        if (security[i] <= security[i + 1]) {
            nonDecreasing[i] = nonDecreasing[i + 1] + 1;
        }
    }
    
    const goodDays = [];
    for (let i = time; i < n - time; i++) {
        if (nonIncreasing[i] >= time && nonDecreasing[i] >= time) {
            goodDays.push(i);
        }
    }
    
    return goodDays;
};
