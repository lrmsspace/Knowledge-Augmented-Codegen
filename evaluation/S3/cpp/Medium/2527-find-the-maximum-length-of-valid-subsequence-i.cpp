// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
// A subsequence sub of nums with length x is called valid if it satisfies:
//
//
// 	(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
//
//
// Return the length of the longest valid subsequence of nums.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 4
//
// Explanation:
//
// The longest valid subsequence is [1, 2, 3, 4].
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 107
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        int ans = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if ((nums[j] + nums[i]) % 2 == 0) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }

        return ans;         
    }
};
