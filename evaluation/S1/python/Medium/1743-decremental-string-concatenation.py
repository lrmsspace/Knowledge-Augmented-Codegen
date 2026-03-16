# Source: https://leetcode.com/problems/decremental-string-concatenation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array words containing n strings.
#
# Let's define a join operation join(x, y) between two strings x and y as concatenating them into xy. However, if the last character of x is equal to the first character of y, one of them is deleted.
#
# For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".
#
# You are to perform n - 1 join operations. Let str0 = words[0]. Starting from i = 1 up to i = n - 1, for the ith operation, you can do one of the following:
#
#
# 	Make stri = join(stri - 1, words[i])
# 	Make stri = join(words[i], stri - 1)
#
#
# Your task is to minimize the length of strn - 1.
#
# Return an integer denoting the minimum possible length of strn - 1.
#
# Example:
# Input: words = ["aa","ab","bc"]
# Output: 4
# Explanation: In this example, we can perform join operations in the following order to minimize the length of str2: 
# str0 = "aa"
# str1 = join(str0, "ab") = "aab"
# str2 = join(str1, "bc") = "aabc" 
# It can be shown that the minimum possible length of str2 is 4.
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 50
# 	Each character in words[i] is an English lowercase letter
#
# Helpful references (internal KB):
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
#   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
#   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
#   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
#   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimizeConcatenatedLength(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        n = len(words)
        dp = [[float('inf')] * 26 for _ in range(26)]
        
        for word in words:
            first_char = ord(word[0]) - ord('a')
            last_char = ord(word[-1]) - ord('a')
            length = len(word)
            
            new_dp = [[float('inf')] * 26 for _ in range(26)]
            
            for i in range(26):
                for j in range(26):
                    if dp[i][j] != float('inf'):
                        # Append word to the end
                        if j == first_char:
                            new_dp[i][last_char] = min(new_dp[i][last_char], dp[i][j] + length - 1)
                        else:
                            new_dp[i][last_char] = min(new_dp[i][last_char], dp[i][j] + length)
                        
                        # Prepend word to the beginning
                        if first_char == i:
                            new_dp[last_char][j] = min(new_dp[last_char][j], dp[i][j] + length - 1)
                        else:
                            new_dp[last_char][j] = min(new_dp[last_char][j], dp[i][j] + length)
            
            # Initialize for the first word
            new_dp[first_char][last_char] = min(new_dp[first_char][last_char], length)
            
            dp = new_dp
        
        return min(dp[i][j] for i in range(26) for j in range(26))