# Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given 3 positive integers zero, one, and limit.
#
# A binary array arr is called stable if:
#
#
# 	The number of occurrences of 0 in arr is exactly zero.
# 	The number of occurrences of 1 in arr is exactly one.
# 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
#
#
# Return the total number of stable binary arrays.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: zero = 1, one = 1, limit = 2
#
# Output: 2
#
# Explanation:
#
# The two possible stable binary arrays are [1,0] and [0,1].
#
# Constraints:
# 1 <= zero, one, limit <= 1000
#
# Helpful references (internal KB):
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
# - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
#   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
#   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
#   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
#   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
#   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfStableArrays(self, zero, one, limit):
        """
        :type zero: int
        :type one: int
        :type limit: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Precompute binomial coefficients
        C = [[0] * (zero + one + 1) for _ in range(zero + one + 1)]
        for i in range(zero + one + 1):
            C[i][0] = 1
            for j in range(1, i + 1):
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD

        # Precompute the number of connected graphs with s vertices
        C_s = [0] * (zero + one + 1)
        C_s[0] = 1
        for s in range(1, zero + one + 1):
            C_s[s] = pow(2, s * (s - 1) // 2, MOD)  # Total graphs
            for k in range(1, s):
                C_s[s] = (C_s[s] - C[s][k] * C_s[k]) % MOD

        # Dynamic programming table D[n][k]
        D = [[0] * (one + 2) for _ in range(zero + one + 2)]
        D[0][0] = 1

        for n in range(1, zero + one + 2):
            for k in range(1, min(n, one) + 2):
                D[n][k] = (D[n - 1][k - 1] * k + D[n - 1][k] * n) % MOD

        # Calculate the total number of stable binary arrays
        result = 0
        for k in range(1, min(one, zero) + 2):
            if k <= zero and k <= one:
                result = (result + C[zero][k] * C[one][k] * D[zero + one - k][k]) % MOD

        return result