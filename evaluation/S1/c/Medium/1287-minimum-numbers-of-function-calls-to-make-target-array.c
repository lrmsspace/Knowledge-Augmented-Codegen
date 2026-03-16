// Source: https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You have an integer array arr of the same length with all values set to 0 initially. You also have the following modify function:
//
// You want to use the modify function to convert arr to nums using the minimum number of calls.
//
// Return the minimum number of function calls to make nums from arr.
//
// The test cases are generated so that the answer fits in a 32-bit signed integer.
//
// Example:
// Input: nums = [1,5]
// Output: 5
// Explanation: Increment by 1 (second element): [0, 0] to get [0, 1] (1 operation).
// Double all the elements: [0, 1] -> [0, 2] -> [0, 4] (2 operations).
// Increment by 1 (both elements)  [0, 4] -> [1, 4] -> [1, 5] (2 operations).
// Total of operations: 1 + 2 + 2 = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
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
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums, int numsSize) {
    int operations = 0;
    int maxBits = 0;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int bits = 0;

        while (num > 0) {
            if (num & 1) {
                operations++;  // Increment operation for each set bit
            }
            num >>= 1;
            bits++;
        }
        if (bits > maxBits) {
            maxBits = bits;  // Track the maximum number of bits needed
        }
    }

    operations += (maxBits > 0) ? (maxBits - 1) : 0;  // Add doubling operations

    return operations;      
}
