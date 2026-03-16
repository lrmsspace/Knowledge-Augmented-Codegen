// Source: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary array nums and an integer k.
//
// A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
//
// Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,1,0], k = 1
// Output: 2
// Explanation: Flip nums[0], then flip nums[2].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= k <= nums.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minKBitFlips = function(nums, k) {
    const n = nums.length;
    const flipEffect = new Array(n).fill(0);
    let flips = 0, currentFlips = 0;

    for (let i = 0; i < n; i++) {
        currentFlips += flipEffect[i];

        if ((nums[i] + currentFlips) % 2 === 0) {
            if (i + k > n) {
                return -1;
            }
            flips++;
            currentFlips++;
            if (i + k < n) {
                flipEffect[i + k]--;
            }
        }
    }

    return flips;
};
