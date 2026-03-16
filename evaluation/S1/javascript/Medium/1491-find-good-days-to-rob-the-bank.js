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
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
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
    const nonIncreasing = Array(n).fill(0);
    const nonDecreasing = Array(n).fill(0);
    const goodDays = [];

    // Calculate non-increasing days before each day
    for (let i = 1; i < n; i++) {
        if (security[i] <= security[i - 1]) {
            nonIncreasing[i] = nonIncreasing[i - 1] + 1;
        }
    }

    // Calculate non-decreasing days after each day
    for (let i = n - 2; i >= 0; i--) {
        if (security[i] <= security[i + 1]) {
            nonDecreasing[i] = nonDecreasing[i + 1] + 1;
        }
    }

    // Identify good days to rob the bank
    for (let i = time; i < n - time; i++) {
        if (nonIncreasing[i] >= time && nonDecreasing[i] >= time) {
            goodDays.push(i);
        }
    }

    return goodDays;
};
