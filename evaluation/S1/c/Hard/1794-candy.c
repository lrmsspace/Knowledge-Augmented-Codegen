// Source: https://leetcode.com/problems/candy/   |   Difficulty: Hard
//
// Problem Description:
// There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
//
// You are giving candies to these children subjected to the following requirements:
//
//
// 	Each child must have at least one candy.
// 	Children with a higher rating get more candies than their neighbors.
//
//
// Return the minimum number of candies you need to have to distribute the candies to the children.
//
// Example:
// Input: ratings = [1,0,2]
// Output: 5
// Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
//
// Constraints:
// n == ratings.length
// 	1 <= n <= 2 * 104
// 	0 <= ratings[i] <= 2 * 104
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
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

int candy(int* ratings, int ratingsSize) {
    if (ratingsSize <= 1) return ratingsSize;

    int *left = (int*)malloc(ratingsSize * sizeof(int));
    int *right = (int*)malloc(ratingsSize * sizeof(int));
    if (!left || !right) {
        free(left); free(right);
        return 0; /* allocation failure */
    }

    /* left to right pass */
    left[0] = 1;
    for (int i = 1; i < ratingsSize; ++i) {
        if (ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
        else left[i] = 1;
    }

    /* right to left pass */
    right[ratingsSize - 1] = 1;
    for (int i = ratingsSize - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) right[i] = right[i + 1] + 1;
        else right[i] = 1;
    }

    /* calculate total candies needed */
    int total = 0;
    for (int i = 0; i < ratingsSize; ++i) {
        total += (left[i] > right[i]) ? left[i] : right[i];
    }

    free(left);
    free(right);
    return total;       
}
