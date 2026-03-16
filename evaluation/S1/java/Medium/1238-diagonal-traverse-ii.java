// Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
//
// Example:
// Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i].length <= 105
// 	1 <= sum(nums[i].length) <= 105
// 	1 <= nums[i][j] <= 105
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Catalan Numbers (number, counting)
//   • When to use: Use when counting arrangements of objects that follow a specific non-crossing or balancing rule, often involving recursive decomposition or paths constrained by a diagonal.
//   • Idea: Catalan numbers count the number of ways to arrange certain combinatorial objects, such as balanced parentheses sequences or monotonic paths that do not cross a diagonal. They can be computed using a recurrence relation (O(N^2) with DP) or a direct binomial coefficient formula (O(N) or O(N log N)).
//   • Invariants: dp[i] stores the i-th Catalan number, correctly computed from dp[0] through dp[i-1].; For each n, the sum sum(dp[k] * dp[n-1-k]) iterates through all valid partitions of the problem.
//   • Tips: Memoize the recursive solution to avoid redundant computations, transforming it into dynamic programming.; For large N, use modular arithmetic if results are required modulo a prime to prevent integer overflow.
//   • Pitfalls: Forgetting to correctly handle the base cases, typically C0 = 1 and C1 = 1.; Encountering integer overflow when calculating large binomial coefficients without appropriate modular arithmetic.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] findDiagonalOrder(List<List<Integer>> nums) {
        Map<Integer, List<Integer>> diagonalMap = new HashMap<>();
        int maxDiagonal = 0;
        int totalElements = 0;

        // Populate the diagonal map
        for (int r = 0; r < nums.size(); r++) {
            List<Integer> row = nums.get(r);
            for (int c = 0; c < row.size(); c++) {
                diagonalMap.putIfAbsent(r + c, new ArrayList<>());
                diagonalMap.get(r + c).add(row.get(c));
                maxDiagonal = Math.max(maxDiagonal, r + c);
                totalElements++;
            }
        }

        int[] result = new int[totalElements];
        int index = 0;

        // Collect elements in diagonal order
        for (int d = 0; d <= maxDiagonal; d++) {
            List<Integer> diagonalList = diagonalMap.get(d);
            if (diagonalList != null) {
                for (int i = diagonalList.size() - 1; i >= 0; i--) {
                    result[index++] = diagonalList.get(i);
                }
            }
        }

        return result;          
    }
}
