// Source: https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays of the same length nums1 and nums2. In one operation, you are allowed to swap nums1[i] with nums2[i].
//
//
// 	For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap the element at i = 3 to obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].
//
//
// Return the minimum number of needed operations to make nums1 and nums2 strictly increasing. The test cases are generated so that the given input always makes it possible.
//
// An array arr is strictly increasing if and only if arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1].
//
// Example:
// Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
// Output: 1
// Explanation: 
// Swap nums1[3] and nums2[3]. Then the sequences are:
// nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
// which are both strictly increasing.
//
// Constraints:
// 2 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 2 * 105
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minSwap(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int swap = 1, noSwap = 0;

        for (int i = 1; i < n; i++) {
            boolean canSwap = nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1];
            boolean canNoSwap = nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1];

            if (canSwap && canNoSwap) {
                swap = Math.min(swap, noSwap) + 1;
                noSwap = swap - 1;
            } else if (canSwap) {
                swap++;
            } else if (canNoSwap) {
                noSwap++;
            } else {
                return -1; // Not possible to make sequences strictly increasing
            }
        }

        return Math.min(swap, noSwap);          
    }
}
