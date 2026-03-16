// Source: https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/   |   Difficulty: Hard
//
// Problem Description:
// You want to build some obstacle courses. You are given a 0-indexed integer array obstacles of length n, where obstacles[i] describes the height of the ith obstacle.
//
// For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course in obstacles such that:
//
//
// 	You choose any number of obstacles between 0 and i inclusive.
// 	You must include the ith obstacle in the course.
// 	You must put the chosen obstacles in the same order as they appear in obstacles.
// 	Every obstacle (except the first) is taller than or the same height as the obstacle immediately before it.
//
//
// Return an array ans of length n, where ans[i] is the length of the longest obstacle course for index i as described above.
//
// Example:
// Input: obstacles = [1,2,3,2]
// Output: [1,2,3,3]
// Explanation: The longest valid obstacle course at each position is:
// - i = 0: [1], [1] has length 1.
// - i = 1: [1,2], [1,2] has length 2.
// - i = 2: [1,2,3], [1,2,3] has length 3.
// - i = 3: [1,2,3,2], [1,2,2] has length 3.
//
// Constraints:
// n == obstacles.length
// 	1 <= n <= 105
// 	1 <= obstacles[i] <= 107
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* longestObstacleCourseAtEachPosition(int* obstacles, int obstaclesSize, int* returnSize) {
    int* ans = (int*)malloc(obstaclesSize * sizeof(int));
    int* dp = (int*)malloc(obstaclesSize * sizeof(int));
    int length = 0;

    for (int i = 0; i < obstaclesSize; i++) {
        int left = 0, right = length;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (dp[mid] <= obstacles[i]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        dp[left] = obstacles[i];
        ans[i] = left + 1;
        if (left == length) {
            length++;
        }
    }

    free(dp);
    *returnSize = obstaclesSize;
    return ans;     
}
