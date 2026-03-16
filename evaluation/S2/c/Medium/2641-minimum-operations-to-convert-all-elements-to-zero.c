// Source: https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of size n, consisting of non-negative integers. Your task is to apply some (possibly zero) operations on the array so that all elements become 0.
//
// In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum non-negative integer in that subarray to 0.
//
// Return the minimum number of operations required to make all elements in the array 0.
//
// Example:
// Input: nums = [0,2]
//
// Output: 1
//
// Explanation:
//
//
// 	Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0].
// 	Thus, the minimum number of operations required is 1.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Range Minimum Query (array, bitset, bit-fenwick)
//   • When to use: When you need to efficiently query the minimum value within a range and perform point updates on an array. It's suitable for scenarios requiring logarithmic time complexity for both operations.
//   • Idea: A Fenwick tree (BIT) can be adapted to answer Range Minimum Queries and perform point updates in O(log N) time. It achieves this by storing prefix minimums in a tree-like structure, allowing efficient aggregation.
//   • Invariants: Each node `tree[i]` stores the minimum of a specific range `[i - (i & -i) + 1, i]`.; An update to `arr[idx]` correctly propagates the new minimum to all relevant `tree` nodes.
//   • Tips: Adapt standard BIT operations for minimums instead of sums.; Use `min(current_value, new_value)` for updates and queries.
//   • Pitfalls: Standard BIT operations are for sums; direct application for minimums is incorrect.; Querying a range `[L, R]` for minimum is not a simple `query(R) - query(L-1)`.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int* nums, int numsSize) {
    // Step 1: Find the maximum value in the array to determine the size of the frequency array.
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    // Step 2: Create a frequency array to count occurrences of each integer.
    int* freq = (int*)calloc(maxVal + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Step 3: Count the number of operations needed.
    int operations = 0;
    for (int i = 1; i <= maxVal; i++) {
        if (freq[i] > 0) {
            operations++;
        }
    }

    // Clean up allocated memory.
    free(freq);

    return operations;      
}
