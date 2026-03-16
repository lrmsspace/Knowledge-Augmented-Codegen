# Source: https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings, word1 and word2, of equal length. You need to transform word1 into word2.
#
# For this, divide word1 into one or more contiguous substrings. For each substring substr you can perform the following operations:
#
#
#  
#  Replace: Replace the character at any one index of substr with another lowercase English letter.
#  
#  
#  Swap: Swap any two characters in substr.
#  
#  
#  Reverse Substring: Reverse substr.
#  
#
#
# Each of these counts as one operation and each character of each substring can be used in each type of operation at most once (i.e. no single index may be involved in more than one replace, one swap, or one reverse).
#
# Return the minimum number of operations required to transform word1 into word2.
#
# Example:
# Input: word1 = "abcdf", word2 = "dacbe"
#
# Output: 4
#
# Explanation:
#
# Divide word1 into "ab", "c", and "df". The operations are:
#
#
#  For the substring "ab",
#
#  
#   Perform operation of type 3 on "ab" -> "ba".
#   Perform operation of type 1 on "ba" -> "da".
#  
#  
#  For the substring "c" do no operations.
#  For the substring "df",
#  
#   Perform operation of type 1 on "df" -> "bf".
#   Perform operation of type 1 on "bf" -> "be".
#
# Constraints:
# 1 <= word1.length == word2.length <= 100
#  word1 and word2 consist only of lowercase English letters.
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        # Step 1: Calculate the longest common subsequence (LCS) of word1 and word2
        m, n = len(word1), len(word2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + 1
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

        lcs_length = dp[m][n]

        # Step 2: Calculate the minimum operations
        # Operations needed to convert word1 to LCS + Operations needed to convert LCS to word2
        operations = (m - lcs_length) + (n - lcs_length)

        return operations