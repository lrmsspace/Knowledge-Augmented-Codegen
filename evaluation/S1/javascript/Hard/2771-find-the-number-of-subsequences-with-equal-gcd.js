// Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
//
//
// 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
//
//
// Return the total number of such pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 10
//
// Explanation:
//
// The subsequence pairs which have the GCD of their elements equal to 1 are:
//
//
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
// 	([1, 2, 3, 4], [1, 2, 3, 4])
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 200
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
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
 * @return {number}
 */
var subsequencePairCount = function(nums) {
    const mod = 1e9 + 7;
    const maxNum = Math.max(...nums);
    const count = Array(maxNum + 1).fill(0);
    
    for (const num of nums) {
        count[num]++;
    }
    
    const gcdCount = Array(maxNum + 1).fill(0);
    
    for (let i = maxNum; i >= 1; i--) {
        let totalSubseq = 0;
        
        for (let j = i; j <= maxNum; j += i) {
            totalSubseq += count[j];
        }
        
        if (totalSubseq > 0) {
            gcdCount[i] = (pow(2, totalSubseq, mod) - 1 + mod) % mod;
        }
        
        for (let j = 2 * i; j <= maxNum; j += i) {
            gcdCount[i] = (gcdCount[i] - gcdCount[j] + mod) % mod;
        }
    }
    
    let result = 0;
    
    for (let i = 1; i <= maxNum; i++) {
        if (gcdCount[i] > 0) {
            result = (result + (gcdCount[i] * gcdCount[i]) % mod) % mod;
        }
    }
    
    return result;
};
