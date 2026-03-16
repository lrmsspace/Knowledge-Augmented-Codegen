// Source: https://leetcode.com/problems/minimum-index-of-a-valid-split/   |   Difficulty: Medium
//
// Problem Description:
// An element x of an integer array arr of length m is dominant if more than half the elements of arr have a value of x.
//
// You are given a 0-indexed integer array nums of length n with one dominant element.
//
// You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1], but the split is only valid if:
//
//
// 	0 <= i < n - 1
// 	nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.
//
//
// Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j, both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.
//
// Return the minimum index of a valid split. If no valid split exists, return -1.
//
// Example:
// Input: nums = [1,2,2,2]
// Output: 2
// Explanation: We can split the array at index 2 to obtain arrays [1,2,2] and [2]. 
// In array [1,2,2], element 2 is dominant since it occurs twice in the array and 2 * 2 > 3. 
// In array [2], element 2 is dominant since it occurs once in the array and 1 * 2 > 1.
// Both [1,2,2] and [2] have the same dominant element as nums, so this is a valid split. 
// It can be shown that index 2 is the minimum index of a valid split.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums has exactly one dominant element.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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

int minimumIndex(int* nums, int numsSize) {
    int countMapSize = 0;
    int dominantElement = 0;
    int dominantCount = 0;

    // First pass: Find the dominant element and its count
    {
        // Using a simple array as a frequency map since nums[i] can be large
        // but we know there's exactly one dominant element.
        // We will use a temporary array to store counts of elements we encounter.
        // This is not optimal in space but works under the problem constraints.
        int *tempCounts = (int *)calloc(numsSize, sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            int found = 0;
            for (int j = 0; j < countMapSize; j++) {
                if (nums[i] == tempCounts[j * 2]) {
                    tempCounts[j * 2 + 1]++;
                    found = 1;
                    if (tempCounts[j * 2 + 1] > dominantCount) {
                        dominantCount = tempCounts[j * 2 + 1];
                        dominantElement = nums[i];
                    }
                    break;
                }
            }
            if (!found) {
                tempCounts[countMapSize * 2] = nums[i];
                tempCounts[countMapSize * 2 + 1] = 1;
                countMapSize++;
                if (1 > dominantCount) {
                    dominantCount = 1;
                    dominantElement = nums[i];
                }
            }
        }
        free(tempCounts);
    }

    // Second pass: Find the minimum index of a valid split
    int leftCount = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i] == dominantElement) {
            leftCount++;
        }
        int rightCount = dominantCount - leftCount;
        int leftSize = i + 1;
        int rightSize = numsSize - leftSize;

        if (leftCount * 2 > leftSize && rightCount * 2 > rightSize) {
            return i;
        }
    }

    return -1;      
}
