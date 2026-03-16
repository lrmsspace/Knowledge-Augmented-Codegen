// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of n integers, your task is to find the maximum value of k for which there exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing. Specifically, check if there are two subarrays of length k starting at indices a and b (a < b), where:
//
//
// 	Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
// 	The subarrays must be adjacent, meaning b = a + k.
//
//
// Return the maximum possible value of k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,5,7,8,9,2,3,4,3,1]
//
// Output: 3
//
// Explanation:
//
//
// 	The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
// 	The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
// 	These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Longest Increasing Subsequence (array, dp-1d)
//   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
//   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
//   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
//   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxIncreasingSubarrays(List<Integer> nums) {
        int n = nums.size();
        int[] inc = new int[n];
        Arrays.fill(inc, 1);

        for (int i = 1; i < n; i++) {
            if (nums.get(i) > nums.get(i - 1)) {
                inc[i] = inc[i - 1] + 1;
            }
        }

        int maxK = 0;
        for (int i = 0; i < n - 1; i++) {
            if (inc[i] > 1 && inc[i + 1] > 1) {
                maxK = Math.max(maxK, Math.min(inc[i], inc[i + 1]));
            }
        }

        return maxK;            
    }
}
