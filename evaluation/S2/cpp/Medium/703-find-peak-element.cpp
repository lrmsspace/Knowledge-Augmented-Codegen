// Source: https://leetcode.com/problems/find-peak-element/   |   Difficulty: Medium
//
// Problem Description:
// A peak element is an element that is strictly greater than its neighbors.
//
// Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.
//
// You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.
//
// You must write an algorithm that runs in O(log n) time.
//
// Example:
// Input: nums = [1,2,3,1]
// Output: 2
// Explanation: 3 is a peak element and your function should return the index number 2.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-231 <= nums[i] <= 231 - 1
// 	nums[i] != nums[i + 1] for all valid i.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Ternary Search (interval, number, binary-search)
//   • When to use: Use when finding the extremum (maximum or minimum) of a unimodal function over a continuous interval, where the function strictly increases then decreases, or vice versa.
//   • Idea: Ternary search is an optimization algorithm that efficiently finds the extremum (maximum or minimum) of a unimodal function over a continuous interval. It operates in logarithmic time, O(log N), by repeatedly narrowing the search space.
//   • Invariants: The global extremum of the unimodal function is always contained within the current interval [l, r].; The function f(x) remains unimodal on the interval [l, r] throughout the search process.
//   • Tips: For floating-point functions, use a fixed number of iterations (e.g., 100-300) instead of an epsilon threshold for robustness.; The two comparison points m1 and m2 should divide the interval into three roughly equal parts for optimal convergence.
//   • Pitfalls: Applying ternary search to a non-unimodal function will not guarantee finding the global extremum.; Floating-point precision errors can lead to incorrect comparisons or infinite loops if epsilon is too small.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[mid + 1]) {
                // Peak is in the left half (including mid)
                right = mid;
            } else {
                // Peak is in the right half
                left = mid + 1;
            }
        }

        return left; // or right, since left == right           
    }
};
