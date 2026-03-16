# Source: https://leetcode.com/problems/shortest-common-supersequence/   |   Difficulty: Hard
#
# Problem Description:
# Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
#
# A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
#
# Example:
# Input: str1 = "abac", str2 = "cab"
# Output: "cabac"
# Explanation: 
# str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
# str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
# The answer provided is the shortest such string that satisfies these properties.
#
# Constraints:
# 1 <= str1.length, str2.length <= 1000
# 	str1 and str2 consist of lowercase English letters.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestCommonSupersequence(self, str1, str2):
        """
        :type str1: str
        :type str2: str
        :rtype: str
        """
        # Step 1: Find the longest common subsequence (LCS) of str1 and str2
        m, n = len(str1), len(str2)
        dp = [[""] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if str1[i - 1] == str2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + str1[i - 1]
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1], key=len)

        lcs = dp[m][n]

        # Step 2: Build the shortest common supersequence using the LCS
        i, j = 0, 0
        result = []
        
        for c in lcs:
            while i < m and str1[i] != c:
                result.append(str1[i])
                i += 1
            while j < n and str2[j] != c:
                result.append(str2[j])
                j += 1
            result.append(c)
            i += 1
            j += 1
        
        # Append remaining characters from str1 and str2
        result.extend(str1[i:])
        result.extend(str2[j:])
        
        return "".join(result)