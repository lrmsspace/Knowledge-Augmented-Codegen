# Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
#
#
# 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
# 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
#
#
# Return the total number of such pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 10
#
# Explanation:
#
# The subsequence pairs which have the GCD of their elements equal to 1 are:
#
#
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 200
#
# Helpful references (internal KB):
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
# - interval-dp (array, interval-dp)
#   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
#   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
#   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
#   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        MOD = 10**9 + 7
        n = len(nums)

        # Step 1: Count subsequences by their GCD
        gcd_count = defaultdict(int)
        for mask in range(1, 1 << n):
            current_gcd = 0
            for i in range(n):
                if mask & (1 << i):
                    current_gcd = gcd(current_gcd, nums[i])
            gcd_count[current_gcd] += 1

        # Step 2: Calculate pairs of subsequences with the same GCD
        result = 0
        for count in gcd_count.values():
            if count > 1:
                result += count * (count - 1) // 2
                result %= MOD

        return result