// Source: https://leetcode.com/problems/find-the-longest-equal-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// A subarray is called equal if all of its elements are equal. Note that the empty subarray is an equal subarray.
//
// Return the length of the longest possible equal subarray after deleting at most k elements from nums.
//
// A subarray is a contiguous, possibly empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,1,3], k = 3
// Output: 3
// Explanation: It's optimal to delete the elements at index 2 and index 4.
// After deleting them, nums becomes equal to [1, 3, 3, 3].
// The longest equal subarray starts at i = 1 and ends at j = 3 with length equal to 3.
// It can be proven that no longer equal subarrays can be created.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= nums.length
// 	0 <= k <= nums.length
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestEqualSubarray(int* nums, int numsSize, int k) {
    int maxLen = 1;
    int left = 0;
    int count[numsSize + 1];
    for (int i = 0; i <= numsSize; i++) {
        count[i] = 0;
    }
    int maxCount = 0;

    for (int right = 0; right < numsSize; right++) {
        count[nums[right]]++;
        if (count[nums[right]] > maxCount) {
            maxCount = count[nums[right]];
        }

        while ((right - left + 1) - maxCount > k) {
            count[nums[left]]--;
            left++;
            maxCount = 0;
            for (int i = 0; i <= numsSize; i++) {
                if (count[i] > maxCount) {
                    maxCount = count[i];
                }
            }
        }

        if ((right - left + 1) > maxLen) {
            maxLen = right - left + 1;
        }
    }

    return maxLen;      
}
