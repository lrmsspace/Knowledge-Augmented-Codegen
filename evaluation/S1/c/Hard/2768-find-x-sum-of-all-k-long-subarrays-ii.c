// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// nums.length == n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 109
// 	1 <= x <= k <= nums.length
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* findXSum(int* nums, int numsSize, int k, int x, int* returnSize) {
    int n = numsSize;
    long long* result = (long long*)malloc((n - k + 1) * sizeof(long long));
    *returnSize = n - k + 1;

    // Frequency map and count array
    #define MAX_NUMS 100000
    int freq[MAX_NUMS + 1] = {0};
    int countFreq[k + 1];
    memset(countFreq, 0, sizeof(countFreq));

    // Initialize frequency for the first window
    for (int i = 0; i < k; ++i) {
        freq[nums[i]]++;
    }
    for (int i = 0; i <= MAX_NUMS; ++i) {
        if (freq[i] > 0) {
            countFreq[freq[i]]++;
        }
    }

    // Function to calculate x-sum
    auto calculateXSum = [&](int* freq, int* countFreq, int x) -> long long {
        long long sum = 0;
        int remaining = x;
        for (int f = k; f >= 1 && remaining > 0; --f) {
            if (countFreq[f] > 0) {
                int take = (countFreq[f] < remaining) ? countFreq[f] : remaining;
                for (int num = MAX_NUMS; num >= 0 && take > 0; --num) {
                    if (freq[num] == f) {
                        sum += (long long)num * f;
                        take--;
                        remaining--;
                    }
                }
            }
        }
        return sum;
    };

    // Calculate x-sum for the first window
    result[0] = calculateXSum(freq, countFreq, x);

    // Slide the window
    for (int i = 1; i <= n - k; ++i) {
        // Remove the element going out of the window
        int outNum = nums[i - 1];
        int outFreq = freq[outNum];
        countFreq[outFreq]--;
        freq[outNum]--;
        if (freq[outNum] > 0) {
            countFreq[freq[outNum]]++;
        }

        // Add the new element coming into the window
        int inNum = nums[i + k - 1];
        int inFreq = freq[inNum];
        if (inFreq > 0) {
            countFreq[inFreq]--;
        }
        freq[inNum]++;
        countFreq[freq[inNum]]++;

        // Calculate x-sum for the current window
        result[i] = calculateXSum(freq, countFreq, x);
    }
    return result;
}
