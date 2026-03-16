// Source: https://leetcode.com/problems/three-consecutive-odds/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.
//
// Example:
// Input: arr = [2,6,4,1]
// Output: false
// Explanation: There are no three consecutive odds.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	1 <= arr[i] <= 1000
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Ternary Search (interval, number, binary-search, greedy)
//   • When to use: Use when searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is a divide and conquer algorithm that finds the extremum of a unimodal function within an interval by repeatedly reducing the search space by approximately one-third. It has a logarithmic time complexity, similar to binary search, but requires two function evaluations per step.
//   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with the function value at m2.
//   • Tips: Handle discrete intervals by checking remaining points when interval size is small.; Consider Golden Section Search to reduce function evaluations per iteration.
//   • Pitfalls: Incorrectly applying to non-unimodal functions.; Infinite loops if stopping condition for discrete intervals is not handled.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        for (int i = 0; i < arr.size() - 2; ++i) {
            if (arr[i] % 2 != 0 && arr[i + 1] % 2 != 0 && arr[i + 2] % 2 != 0) {
                return true;
            }
        }
        return false;           
    }
};
