// Source: https://leetcode.com/problems/make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. In one operation, you can select a subarray and replace it with a single element equal to its maximum value.
//
// Return the maximum possible size of the array after performing zero or more operations such that the resulting array is non-decreasing.
//
// Example:
// Input: nums = [4,2,5,3,5]
//
// Output: 3
//
// Explanation:
//
// One way to achieve the maximum size is:
//
//
// 	Replace subarray nums[1..2] = [2, 5] with 5 → [4, 5, 3, 5].
// 	Replace subarray nums[2..3] = [3, 5] with 5 → [4, 5, 5].
//
//
// The final array [4, 5, 5] is non-decreasing with size 3.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 2 * 105
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
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
    public int maximumPossibleSize(int[] nums) {
        int n = nums.length;
        int[] tails = new int[n];
        int size = 0;

        for (int num : nums) {
            int left = 0, right = size;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (tails[mid] <= num) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            tails[left] = num;
            if (left == size) {
                size++;
            }
        }

        return size;            
    }
}
