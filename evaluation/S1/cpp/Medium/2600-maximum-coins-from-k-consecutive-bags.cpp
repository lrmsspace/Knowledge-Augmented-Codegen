// Source: https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/   |   Difficulty: Medium
//
// Problem Description:
// There are an infinite amount of bags on a number line, one bag for each coordinate. Some of these bags contain coins.
//
// You are given a 2D array coins, where coins[i] = [li, ri, ci] denotes that every bag from li to ri contains ci coins.
//
// The segments that coins contain are non-overlapping.
//
// You are also given an integer k.
//
// Return the maximum amount of coins you can obtain by collecting k consecutive bags.
//
// Example:
// Input: coins = [[8,10,1],[1,3,2],[5,6,4]], k = 4
//
// Output: 10
//
// Explanation:
//
// Selecting bags at positions [3, 4, 5, 6] gives the maximum number of coins: 2 + 0 + 4 + 4 = 10.
//
// Constraints:
// 1 <= coins.length <= 105
// 	1 <= k <= 109
// 	coins[i] == [li, ri, ci]
// 	1 <= li <= ri <= 109
// 	1 <= ci <= 1000
// 	The given segments are non-overlapping.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        // Collect all relevant positions (segment endpoints and k-length window endpoints)
        vector<long long> positions;
        for (auto &seg : coins) {
            positions.push_back(seg[0]);
            positions.push_back(seg[1] + 1); // exclusive end
        }
        for (auto &seg : coins) {
            if (seg[0] - k >= 1) positions.push_back(seg[0] - k);
            positions.push_back(seg[1] + 1 - k);
        }
        positions.push_back(1); // leftmost possible window start

        // Coordinate compress positions
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());

        // Build difference array for coin counts
        vector<long long> diff(positions.size() + 1, 0);
        for (auto &seg : coins) {
            int l = lower_bound(positions.begin(), positions.end(), seg[0]) - positions.begin();
            int r = lower_bound(positions.begin(), positions.end(), seg[1] + 1) - positions.begin();
            diff[l] += seg[2];
            diff[r] -= seg[2];
        }

        // Build prefix sum array for coin counts
        vector<long long> coinCount(positions.size(), 0);
        long long curr = 0;
        for (size_t i = 0; i < positions.size(); ++i) {
            curr += diff[i];
            coinCount[i] = curr;
        }

        // Sliding window to find max coins in any k-length segment
        long long maxCoins = 0;
        long long windowSum = 0;
        size_t left = 0;
        for (size_t right = 0; right < positions.size(); ++right) {
            if (right > 0) {
                windowSum += coinCount[right - 1] * (positions[right] - positions[right - 1]);
            }
            while (positions[right] - positions[left] > k) {
                windowSum -= coinCount[left] * (positions[left + 1] - positions[left]);
                ++left;
            }
            maxCoins = max(maxCoins, windowSum);
        }

        return maxCoins;            
    }
};
