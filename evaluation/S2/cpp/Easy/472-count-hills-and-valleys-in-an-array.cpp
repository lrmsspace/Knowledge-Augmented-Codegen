// Source: https://leetcode.com/problems/count-hills-and-valleys-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums. An index i is part of a hill in nums if the closest non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is part of a valley in nums if the closest non-equal neighbors of i are larger than nums[i]. Adjacent indices i and j are part of the same hill or valley if nums[i] == nums[j].
//
// Note that for an index to be part of a hill or valley, it must have a non-equal neighbor on both the left and right of the index.
//
// Return the number of hills and valleys in nums.
//
// Example:
// Input: nums = [2,4,1,1,6,5]
// Output: 3
// Explanation:
// At index 0: There is no non-equal neighbor of 2 on the left, so index 0 is neither a hill nor a valley.
// At index 1: The closest non-equal neighbors of 4 are 2 and 1. Since 4 > 2 and 4 > 1, index 1 is a hill. 
// At index 2: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 2 is a valley.
// At index 3: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 3 is a valley, but note that it is part of the same valley as index 2.
// At index 4: The closest non-equal neighbors of 6 are 1 and 5. Since 6 > 1 and 6 > 5, index 4 is a hill.
// At index 5: There is no non-equal neighbor of 5 on the right, so index 5 is neither a hill nor a valley. 
// There are 3 hills and valleys so we return 3.
//
// Constraints:
// 3 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Ternary Search (interval, number, binary-search)
//   • When to use: Use when finding the extremum (maximum or minimum) of a unimodal function over a continuous interval, where the function strictly increases then decreases, or vice versa.
//   • Idea: Ternary search is an optimization algorithm that efficiently finds the extremum (maximum or minimum) of a unimodal function over a continuous interval. It operates in logarithmic time, O(log N), by repeatedly narrowing the search space.
//   • Invariants: The global extremum of the unimodal function is always contained within the current interval [l, r].; The function f(x) remains unimodal on the interval [l, r] throughout the search process.
//   • Tips: For floating-point functions, use a fixed number of iterations (e.g., 100-300) instead of an epsilon threshold for robustness.; The two comparison points m1 and m2 should divide the interval into three roughly equal parts for optimal convergence.
//   • Pitfalls: Applying ternary search to a non-unimodal function will not guarantee finding the global extremum.; Floating-point precision errors can lead to incorrect comparisons or infinite loops if epsilon is too small.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int count = 0;
        for (int i = 1; i < nums.size() - 1; ++i) {
            int left = i - 1, right = i + 1;
            while (left >= 0 && nums[left] == nums[i]) {
                --left;
            }
            while (right < nums.size() && nums[right] == nums[i]) {
                ++right;
            }
            if (left >= 0 && right < nums.size()) {
                if ((nums[i] > nums[left] && nums[i] > nums[right]) ||
                    (nums[i] < nums[left] && nums[i] < nums[right])) {
                    ++count;
                }
            }
        }
        return count;           
    }
};
