// Source: https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing an array colors of length n where all elements are set to 0's meaning uncolored. You are also given a 2D integer array queries where queries[i] = [indexi, colori]. For the ith query:
//
//
// 	Set colors[indexi] to colori.
// 	Count the number of adjacent pairs in colors which have the same color (regardless of colori).
//
//
// Return an array answer of the same length as queries where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
//
// Output: [0,1,1,0,2]
//
// Explanation:
//
//
// 	Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
// 	After the 1st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
// 	After the 2nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
// 	After the 3rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
// 	After the 4th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
// 	After the 5th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= indexi <= n - 1
// 	1 <=  colori <= 105
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} queries
 * @return {number[]}
 */
var colorTheArray = function(n, queries) {
    const colors = new Array(n).fill(0);
    const result = new Array(queries.length);
    let sameColorPairs = 0;

    for (let i = 0; i < queries.length; i++) {
        const [index, color] = queries[i];
        const oldColor = colors[index];

        // If the cell is already colored, we need to check if it forms same color pairs with neighbors
        if (oldColor !== 0) {
            if (index > 0 && colors[index - 1] === oldColor) {
                sameColorPairs--;
            }
            if (index < n - 1 && colors[index + 1] === oldColor) {
                sameColorPairs--;
            }
        }

        // Update the color of the cell
        colors[index] = color;

        // Check if the new color forms same color pairs with neighbors
        if (color !== 0) {
            if (index > 0 && colors[index - 1] === color) {
                sameColorPairs++;
            }
            if (index < n - 1 && colors[index + 1] === color) {
                sameColorPairs++;
            }
        }

        result[i] = sameColorPairs;
    }

    return result;
};
