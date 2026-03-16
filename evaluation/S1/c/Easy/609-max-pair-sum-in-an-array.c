// Source: https://leetcode.com/problems/max-pair-sum-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the largest digit in both numbers is equal.
//
// For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7 is the largest among them.
//
// Return the maximum sum or -1 if no such pair exists.
//
// Example:
// Input: nums = [112,131,411]
//
// Output: -1
//
// Explanation:
//
// Each numbers largest digit in order is [2,3,4].
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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

int maxSum(int* nums, int numsSize) {
    int max_sum = -1;
    int buckets[10][2]; // Store the top two numbers for each largest digit (0-9)
    
    // Initialize buckets
    for (int i = 0; i < 10; i++) {
        buckets[i][0] = -1; // First max
        buckets[i][1] = -1; // Second max
    }
    
    // Function to find the largest digit in a number
    int largest_digit(int num) {
        int max_digit = 0;
        while (num > 0) {
            int digit = num % 10;
            if (digit > max_digit) {
                max_digit = digit;
            }
            num /= 10;
        }
        return max_digit;
    }
    
    // Populate the buckets with the top two numbers for each largest digit
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int ld = largest_digit(num);
        
        if (num > buckets[ld][0]) {
            buckets[ld][1] = buckets[ld][0];
            buckets[ld][0] = num;
        } else if (num > buckets[ld][1]) {
            buckets[ld][1] = num;
        }
    }
    
    // Calculate the maximum sum from the buckets
    for (int i = 0; i < 10; i++) {
        if (buckets[i][0] != -1 && buckets[i][1] != -1) {
            int current_sum = buckets[i][0] + buckets[i][1];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    
    return max_sum;     
}
