# Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a positive integer k.
#
# Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
#
#
# 	The length of each substring is at least k.
# 	Each substring is a palindrome.
#
#
# Return the maximum number of substrings in an optimal selection.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "abaccdbbd", k = 3
# Output: 2
# Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
# It can be shown that we cannot find a selection with more than two valid substrings.
#
# Constraints:
# 1 <= k <= s.length <= 2000
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxPalindromes(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)

        # Manacher's Algorithm to find all palindromic substrings
        d_odd = [0] * n
        l, r = 0, -1
        for i in range(n):
            k1 = 1 if i > r else min(d_odd[l + r - i], r - i + 1)
            while 0 <= i - k1 and i + k1 < n and s[i - k1] == s[i + k1]:
                k1 += 1
            d_odd[i] = k1
            if i + k1 - 1 > r:
                l, r = i - k1 + 1, i + k1 - 1

        d_even = [0] * n
        l, r = 0, -1
        for i in range(n):
            k2 = 0 if i > r else min(d_even[l + r - i + 1], r - i + 1)
            while 0 <= i - k2 - 1 and i + k2 < n and s[i - k2 - 1] == s[i + k2]:
                k2 += 1
            d_even[i] = k2
            if i + k2 - 1 > r:
                l, r = i - k2, i + k2 - 1

        # Collect all palindromic substrings of length >= k
        palindromes = []
        for center in range(n):
            radius = d_odd[center]
            for r in range(radius):
                length = 2 * r + 1
                if length >= k:
                    palindromes.append((center - r, center + r))

            radius = d_even[center]
            for r in range(radius):
                length = 2 * (r + 1)
                if length >= k:
                    palindromes.append((center - r - 1, center + r))

        # Sort palindromic substrings by starting index
        palindromes.sort()

        # Greedily select non-overlapping palindromic substrings
        result = 0
        last_end = -1
        for start, end in palindromes:
            if start > last_end:
                result += 1
                last_end = end
        return result   