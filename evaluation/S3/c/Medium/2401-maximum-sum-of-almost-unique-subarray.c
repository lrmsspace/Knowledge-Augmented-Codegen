// Source: https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two positive integers m and k.
//
// Return the maximum sum out of all almost unique subarrays of length k of nums. If no such subarray exists, return 0.
//
// A subarray of nums is almost unique if it contains at least m distinct elements.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,6,7,3,1,7], m = 3, k = 4
// Output: 18
// Explanation: There are 3 almost unique subarrays of size k = 4. These subarrays are [2, 6, 7, 3], [6, 7, 3, 1], and [7, 3, 1, 7]. Among these subarrays, the one with the maximum sum is [2, 6, 7, 3] which has a sum of 18.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= m <= k <= nums.length
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
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

long long maxSum(int* nums, int numsSize, int m, int k) {
    long long max_sum = 0;
    long long current_sum = 0;
    int distinct_count = 0;
    int freq[100001] = {0}; // Assuming nums[i] <= 10^5

    for (int i = 0; i < numsSize; i++) {
        // Add the current element to the window
        current_sum += nums[i];
        if (freq[nums[i]] == 0) {
            distinct_count++;
        }
        freq[nums[i]]++;

        // If the window size exceeds k, remove the leftmost element
        if (i >= k) {
            current_sum -= nums[i - k];
            freq[nums[i - k]]--;
            if (freq[nums[i - k]] == 0) {
                distinct_count--;
            }
        }

        // Check if the current window is almost unique and update max_sum
        if (i >= k - 1 && distinct_count >= m) {
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }

    return max_sum;     
}
