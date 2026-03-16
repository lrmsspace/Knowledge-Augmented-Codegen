// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums consisting of 3 * n elements.
//
// You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
//
//
// 	The first n elements belonging to the first part and their sum is sumfirst.
// 	The next n elements belonging to the second part and their sum is sumsecond.
//
//
// The difference in sums of the two parts is denoted as sumfirst - sumsecond.
//
//
// 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
// 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
//
//
// Return the minimum difference possible between the sums of the two parts after the removal of n elements.
//
// Example:
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1. 
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
//
// Constraints:
// nums.length == 3 * n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
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

long long minimumDifference(int* nums, int numsSize) {
    int n = numsSize / 3;
    long long totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum += nums[i];
    }

    /* Min-heap for the first part */
    int *minHeap = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        minHeap[i] = nums[i];
    }
    /* Build initial min-heap */
    for (int i = n / 2 - 1; i >= 0; --i) {
        int parent = i;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;
            if (left < n && minHeap[left] < minHeap[smallest]) smallest = left;
            if (right < n && minHeap[right] < minHeap[smallest]) smallest = right;
            if (smallest == parent) break;
            int temp = minHeap[parent];
            minHeap[parent] = minHeap[smallest];
            minHeap[smallest] = temp;
            parent = smallest;
        }
    }

    long long firstPartSum = 0;
    for (int i = 0; i < n; ++i) {
        firstPartSum += minHeap[i];
    }
    long long *prefixSums = (long long*)malloc((n + 1) * sizeof(long long));
    prefixSums[0] = firstPartSum;

    for (int i = n; i < 2 * n; ++i) {
        if (nums[i] > minHeap[0]) {
            firstPartSum += nums[i] - minHeap[0];
            minHeap[0] = nums[i];
            /* Heapify down */
            int parent = 0;
            while (1) {
                int left = 2 * parent + 1;
                int right = 2 * parent + 2;
                int smallest = parent;
                if (left < n && minHeap[left] < minHeap[smallest]) smallest = left;
                if (right < n && minHeap[right] < minHeap[smallest]) smallest = right;
                if (smallest == parent) break;
                int temp = minHeap[parent];
                minHeap[parent] = minHeap[smallest];
                minHeap[smallest] = temp;
                parent = smallest;
            }
        }
        prefixSums[i - n + 1] = firstPartSum;
    }
    free(minHeap);
    /* Max-heap for the second part */
    int *maxHeap = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        maxHeap[i] = nums[numsSize - 1 - i];
    }

    /* Build initial max-heap */
    for (int i = n / 2 - 1; i >= 0; --i) {
        int parent = i;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;
            if (left < n && maxHeap[left] > maxHeap[largest]) largest = left;
            if (right < n && maxHeap[right] > maxHeap[largest]) largest = right;
            if (largest == parent) break;
            int temp = maxHeap[parent];
            maxHeap[parent] = maxHeap[largest];
            maxHeap[largest] = temp;
            parent = largest;
        }
    }   

    long long secondPartSum = 0;
    for (int i = 0; i < n; ++i) {
        secondPartSum += maxHeap[i];
    }
    long long *suffixSums = (long long*)malloc((n + 1) * sizeof(long long));
    suffixSums[n] = secondPartSum;
    for (int i = 2 * n - 1; i >= n; --i) {
        if (nums[i] < maxHeap[0]) {
            secondPartSum += nums[i] - maxHeap[0];
            maxHeap[0] = nums[i];
            /* Heapify down */
            int parent = 0;
            while (1) {
                int left = 2 * parent + 1;
                int right = 2 * parent + 2;
                int largest = parent;
                if (left < n && maxHeap[left] > maxHeap[largest]) largest = left;
                if (right < n && maxHeap[right] > maxHeap[largest]) largest = right;
                if (largest == parent) break;
                int temp = maxHeap[parent];
                maxHeap[parent] = maxHeap[largest];
                maxHeap[largest] = temp;
                parent = largest;
            }
        }
        suffixSums[i - n] = secondPartSum;
    }
    free(maxHeap);  
    /* Find minimum difference */
    long long minDifference = prefixSums[0] - suffixSums[0];
    for (int i = 0; i <= n; ++i) {
        long long currentDifference = prefixSums[i] - suffixSums[i];
        if (currentDifference < minDifference) {
            minDifference = currentDifference;
        }
    }
    free(prefixSums);
    free(suffixSums);
    return minDifference;
}