// Source: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// You are allowed to perform the following operation on each element of the array at most once:
//
//
// 	Add an integer in the range [-k, k] to the element.
//
//
// Return the maximum possible number of distinct elements in nums after performing the operations.
//
// Example:
// Input: nums = [1,2,2,3,3,4], k = 2
//
// Output: 6
//
// Explanation:
//
// nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxDistinctElements(int* nums, int numsSize, int k) {
    #define HASH_SIZE 131071  // A large prime number for hash table size

    int hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hash[i] = 0;
    }

    int distinct_count = 0;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int found = 0;

        // Check if num - k is in the hash
        if (k > 0) {
            int candidate = num - k;
            int hash_index = candidate % HASH_SIZE;
            if (hash_index < 0) hash_index += HASH_SIZE;

            while (hash[hash_index] != 0) {
                if (hash[hash_index] == candidate) {
                    found = 1;
                    break;
                }
                hash_index = (hash_index + 1) % HASH_SIZE;
            }
        }

        // If not found, check num + k
        if (!found && k > 0) {
            int candidate = num + k;
            int hash_index = candidate % HASH_SIZE;
            if (hash_index < 0) hash_index += HASH_SIZE;

            while (hash[hash_index] != 0) {
                if (hash[hash_index] == candidate) {
                    found = 1;
                    break;
                }
                hash_index = (hash_index + 1) % HASH_SIZE;
            }
        }

        // If still not found, try to insert num
        if (!found) {
            int candidate = num;
            int hash_index = candidate % HASH_SIZE;
            if (hash_index < 0) hash_index += HASH_SIZE;

            while (hash[hash_index] != 0) {
                if (hash[hash_index] == candidate) {
                    found = 1;
                    break;
                }
                hash_index = (hash_index + 1) % HASH_SIZE;
            }

            if (!found) {
                hash[hash_index] = candidate;
                distinct_count++;
            }
        } else {
            distinct_count++;
        }
    }

    return distinct_count;      
}
