// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @param {number[]} limits
 * @param {number} k
 * @return {number}
 */
var maxSum = function(grid, limits, k) {
    const n = grid.length;
    const m = grid[0].length;
    
    // Step 1: For each row, sort the elements in descending order and compute prefix sums
    const prefixSums = [];
    for (let i = 0; i < n; i++) {
        const sortedRow = grid[i].slice().sort((a, b) => b - a);
        const limitedRow = sortedRow.slice(0, limits[i]);
        const prefixSum = [0];
        for (const val of limitedRow) {
            prefixSum.push(prefixSum[prefixSum.length - 1] + val);
        }
        prefixSums.push(prefixSum);
    }
    
    // Step 2: Use a min-heap to find the maximum sum of at most k elements
    let maxTotalSum = 0;
    const heap = new MinPriorityQueue({ priority: x => x.sum });
    
    // Initialize the heap with the first element from each row's prefix sums
    for (let i = 0; i < n; i++) {
        if (prefixSums[i].length > 1) { // Check if there's at least one element to take
            heap.enqueue({ sum: prefixSums[i][1], row: i, count: 1 });
        }
    }
    
    // Extract the maximum sum from the heap up to k times
    for (let count = 0; count < k && !heap.isEmpty(); count++) {
        const { sum, row, count: currentCount } = heap.dequeue().element;
        maxTotalSum += sum;
        
        // If we can take more from this row, enqueue the next prefix sum
        if (currentCount + 1 < prefixSums[row].length) {
            heap.enqueue({ sum: prefixSums[row][currentCount + 1], row: row, count: currentCount + 1 });
        }
    }
    
    return maxTotalSum;
};
