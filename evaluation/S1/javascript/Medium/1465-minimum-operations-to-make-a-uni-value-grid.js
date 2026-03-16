// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.
//
// A uni-value grid is a grid where all the elements of it are equal.
//
// Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.
//
// Example:
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following: 
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= x, grid[i][j] <= 104
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Chinese Remainder Theorem (number, recursion, mod-exp)
//   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
//   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
//   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @param {number} x
 * @return {number}
 */
var minOperations = function(grid, x) {
    const m = grid.length;
    const n = grid[0].length;
    const flatGrid = [];

    // Flatten the grid and check feasibility
    const remainder = grid[0][0] % x;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] % x !== remainder) {
                return -1; // Not possible to make all elements equal
            }
            flatGrid.push(grid[i][j]);
        }
    }

    // Find the median
    flatGrid.sort((a, b) => a - b);
    const median = flatGrid[Math.floor(flatGrid.length / 2)];

    // Calculate the total operations to make all elements equal to the median
    let operations = 0;
    for (const value of flatGrid) {
        operations += Math.abs(value - median) / x;
    }

    return operations;
};
