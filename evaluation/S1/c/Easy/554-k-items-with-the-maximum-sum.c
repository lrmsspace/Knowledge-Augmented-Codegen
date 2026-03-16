// Source: https://leetcode.com/problems/k-items-with-the-maximum-sum/   |   Difficulty: Easy
//
// Problem Description:
// There is a bag that consists of items, each item has a number 1, 0, or -1 written on it.
//
// You are given four non-negative integers numOnes, numZeros, numNegOnes, and k.
//
// The bag initially contains:
//
//
// 	numOnes items with 1s written on them.
// 	numZeroes items with 0s written on them.
// 	numNegOnes items with -1s written on them.
//
//
// We want to pick exactly k items among the available items. Return the maximum possible sum of numbers written on the items.
//
// Example:
// Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 2
// Output: 2
// Explanation: We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take 2 items with 1 written on them and get a sum in a total of 2.
// It can be proven that 2 is the maximum possible sum.
//
// Constraints:
// 0 <= numOnes, numZeros, numNegOnes <= 50
// 	0 <= k <= numOnes + numZeros + numNegOnes
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
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

int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
    int sum = 0;

    if (k <= numOnes) {
        sum = k;
    } else if (k <= numOnes + numZeros) {
        sum = numOnes;
    } else {
        sum = numOnes - (k - numOnes - numZeros);
    }

    return sum;     
}
