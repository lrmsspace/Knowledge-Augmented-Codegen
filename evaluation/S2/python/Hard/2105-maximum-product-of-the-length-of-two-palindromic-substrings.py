# Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
#
# More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
#
# Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
#
# A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: s = "ababbb"
# Output: 9
# Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
#
# Constraints:
# 2 <= s.length <= 105
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
    def maxProduct(self, s):
        """
        :type s: str
        :rtype: int
        """
        def manacher(s):
            n = len(s)
            d_odd = [0] * n  # d_odd[i] will store the radius of the longest odd-length palindrome centered at i
            l, r = 0, -1  # (l, r) is the rightmost palindrome found so far

            for i in range(n):
                k = 1 if i > r else min(d_odd[l + r - i], r - i + 1)
                while i - k >= 0 and i + k < n and s[i - k] == s[i + k]:
                    k += 1
                d_odd[i] = k
                k -= 1
                if i + k > r:
                    l, r = i - k, i + k
            
            return d_odd
        
        d_odd = manacher(s)
        max_product = 0
        
        # We will keep track of the maximum odd palindrome length to the left of each index
        max_left = [0] * len(s)
        max_len = 0
        
        for i in range(len(s)):
            max_len = max(max_len, 2 * d_odd[i] - 1)  # Length of the palindrome centered at i
            max_left[i] = max_len
        
        # Now we will check for palindromes to the right and calculate products
        max_len_right = 0
        
        for j in range(len(s) - 1, -1, -1):
            max_len_right = max(max_len_right, 2 * d_odd[j] - 1)  # Length of the palindrome centered at j
            if j < len(s) - 1:
                max_product = max(max_product, max_left[j] * max_len_right)
        
        return max_product