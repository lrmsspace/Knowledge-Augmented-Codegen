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
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
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
    
    // Calculate non-increasing counts
    for (let i = 1; i < n; i++) {
        if (security[i] <= security[i - 1]) {
            nonIncreasing[i] = nonIncreasing[i - 1] + 1;
        }
    }
    
    // Calculate non-decreasing counts
    for (let i = n - 2; i >= 0; i--) {
        if (security[i] <= security[i + 1]) {
            nonDecreasing[i] = nonDecreasing[i + 1] + 1;
        }
    }
    
    const goodDays = [];
    
    // Determine good days
    for (let i = time; i < n - time; i++) {
        if (nonIncreasing[i] >= time && nonDecreasing[i] >= time) {
            goodDays.push(i);
        }
    }
    
    return goodDays;
};
