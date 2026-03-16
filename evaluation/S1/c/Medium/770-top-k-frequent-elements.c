// Source: https://leetcode.com/problems/top-k-frequent-elements/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
//
// Example:
// Input: nums = [1,1,1,2,2,3], k = 2
//
// Output: [1,2]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	k is in the range [1, the number of unique elements in the array].
// 	It is guaranteed that the answer is unique.
//
//
//  
// Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
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
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    #define MAX_NUM 10000
    #define OFFSET 10000
    int freq[2 * MAX_NUM + 1] = {0};
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i] + OFFSET]++;
    }

    // Bucket sort based on frequency
    int** buckets = (int**)calloc(numsSize + 1, sizeof(int*));
    int* bucketSizes = (int*)calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i <= 2 * MAX_NUM; ++i) {
        if (freq[i] > 0) {
            int f = freq[i];
            if (buckets[f] == NULL) {
                buckets[f] = (int*)malloc(numsSize * sizeof(int));
            }
            buckets[f][bucketSizes[f]++] = i - OFFSET;
        }
    }

    int* result = (int*)malloc(k * sizeof(int));
    int count = 0;
    for (int f = numsSize; f >= 1 && count < k; --f) {
        if (buckets[f] != NULL) {
            for (int j = 0; j < bucketSizes[f] && count < k; ++j) {
                result[count++] = buckets[f][j];
            }
            free(buckets[f]);
        }
    }

    free(buckets);
    free(bucketSizes);
    *returnSize = k;
    return result;      
}
