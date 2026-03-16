// Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums.
//
// A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.
//
// Return the total number of incremovable subarrays of nums.
//
// Note that an empty array is considered strictly increasing.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 10
// Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long incremovableSubarrayCount(int* nums, int numsSize) {
    // Step 1: Calculate the length of the longest increasing subsequence (LIS) for each prefix and suffix
    int* lis_from_left = (int*)malloc(numsSize * sizeof(int));
    int* lis_from_right = (int*)malloc(numsSize * sizeof(int));
    
    // Calculate LIS from the left
    for (int i = 0; i < numsSize; i++) {
        lis_from_left[i] = 1; // Each element is an increasing subsequence of length 1
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (lis_from_left[j] + 1 > lis_from_left[i]) {
                    lis_from_left[i] = lis_from_left[j] + 1;
                }
            }
        }
    }
    
    // Calculate LIS from the right
    for (int i = numsSize - 1; i >= 0; i--) {
        lis_from_right[i] = 1; // Each element is an increasing subsequence of length 1
        for (int j = numsSize - 1; j > i; j--) {
            if (nums[j] > nums[i]) {
                if (lis_from_right[j] + 1 > lis_from_right[i]) {
                    lis_from_right[i] = lis_from_right[j] + 1;
                }
            }
        }
    }
    
    // Step 2: Count the number of incremovable subarrays
    long long count = 0;
    
    // A subarray [i, j] is incremovable if:
    // - The longest increasing subsequence from the left up to index i-1 plus the longest increasing subsequence from the right starting at index j+1 is at least the length of the original array minus the length of the subarray.
    for (int i = 0; i < numsSize; i++) {
        for (int j = i; j < numsSize; j++) {
            int left_lis_length = (i > 0) ? lis_from_left[i - 1] : 0;
            int right_lis_length = (j < numsSize - 1) ? lis_from_right[j + 1] : 0;
            if (left_lis_length + right_lis_length >= numsSize - (j - i + 1)) {
                count++;
            }
        }
        
    }
    free(lis_from_left);
    free(lis_from_right);
    return count;
}
