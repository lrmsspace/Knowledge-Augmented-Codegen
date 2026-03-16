// Source: https://leetcode.com/problems/maximum-gap/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
//
// You must write an algorithm that runs in linear time and uses linear extra space.
//
// Example:
// Input: nums = [3,6,9,1]
// Output: 3
// Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumGap(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    int minVal = nums[0], maxVal = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < minVal) minVal = nums[i];
        else if (nums[i] > maxVal) maxVal = nums[i];
    }
    if (minVal == maxVal) return 0;

    int bucketSize = (maxVal - minVal) / (numsSize - 1);
    if ((maxVal - minVal) % (numsSize - 1)) ++bucketSize;

    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    int *bucketMin = (int*)malloc(bucketCount * sizeof(int));
    int *bucketMax = (int*)malloc(bucketCount * sizeof(int));
    if (!bucketMin || !bucketMax) {
        free(bucketMin); free(bucketMax); return 0; /* allocation failure */
    }
    for (int i = 0; i < bucketCount; ++i) {
        bucketMin[i] = -1;
        bucketMax[i] = -1;
    }

    for (int i = 0; i < numsSize; ++i) {
        int bIdx = (nums[i] - minVal) / bucketSize;
        if (bucketMin[bIdx] == -1 || nums[i] < bucketMin[bIdx]) {
            bucketMin[bIdx] = nums[i];
        }
        if (bucketMax[bIdx] == -1 || nums[i] > bucketMax[bIdx]) {
            bucketMax[bIdx] = nums[i];
        }
    }

    int maxGap = 0;
    int prevMax = -1;
    for (int i = 0; i < bucketCount; ++i) {
        if (bucketMin[i] == -1) continue;
        if (prevMax != -1) {
            int gap = bucketMin[i] - prevMax;
            if (gap > maxGap) maxGap = gap;
        }
        prevMax = bucketMax[i];
    }

    free(bucketMin);
    free(bucketMax);
    return maxGap;      
}
