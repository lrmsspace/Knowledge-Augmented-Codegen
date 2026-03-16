// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums and an integer target, return the maximum number of non-empty non-overlapping subarrays such that the sum of values in each subarray is equal to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 2
// Output: 2
// Explanation: There are 2 non-overlapping subarrays [1,1,1,1,1] with sum equals to target(2).
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	0 <= target <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxNonOverlapping(int* nums, int numsSize, int target) {
    int count = 0;
    int prefix_sum = 0;
    // Use a hash set to store the prefix sums we have seen
    // We can use a simple array since the range of prefix sums can be large
    // but we will use a fixed size array for simplicity
    #define HASH_SIZE 200003
    int hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hash[i] = 0;
    }
    hash[0] = 1; // base case: prefix sum of 0 is seen

    for (int i = 0; i < numsSize; i++) {
        prefix_sum += nums[i];
        int needed_sum = prefix_sum - target;
        int hash_index = (needed_sum % HASH_SIZE + HASH_SIZE) % HASH_SIZE;

        if (hash[hash_index]) {
            count++;
            // Reset for non-overlapping
            prefix_sum = 0;
            for (int j = 0; j < HASH_SIZE; j++) {
                hash[j] = 0;
            }
            hash[0] = 1; // reset base case
        } else {
            hash[(prefix_sum % HASH_SIZE + HASH_SIZE) % HASH_SIZE] = 1;
        }
    }

    return count;       
}
