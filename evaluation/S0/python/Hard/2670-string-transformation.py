# Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings s and t of equal length n. You can perform the following operation on the string s:
#
#
# 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
# 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
#
#
# You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
#
# Since the answer can be large, return it modulo 109 + 7.
#
# Example:
# Input: s = "abcd", t = "cdab", k = 2
# Output: 2
# Explanation: 
# First way:
# In first operation, choose suffix from index = 3, so resulting s = "dabc".
# In second operation, choose suffix from index = 3, so resulting s = "cdab".
#
# Second way:
# In first operation, choose suffix from index = 1, so resulting s = "bcda".
# In second operation, choose suffix from index = 1, so resulting s = "cdab".
#
# Constraints:
# 2 <= s.length <= 5 * 105
# 	1 <= k <= 1015
# 	s.length == t.length
# 	s and t consist of only lowercase English alphabets.
#

class Solution(object):
    def numberOfWays(self, s, t, k):
        """
        :type s: str
        :type t: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)

        # Count the number of rotations needed to convert s to t
        def count_rotations(s, t):
            for i in range(n):
                if s == t:
                    return i
                s = s[1:] + s[0]
            return -1

        rotations_needed = count_rotations(s, t)
        if rotations_needed == -1:
            return 0

        # DP table to store the number of ways
        dp = [[0] * 2 for _ in range(k + 1)]
        dp[0][0] = 1  # 0 operations, same string
        dp[0][1] = 0  # 0 operations, different string

        for i in range(1, k + 1):
            dp[i][0] = (dp[i - 1][1] * (n - 1)) % MOD
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] * (n - 2)) % MOD

        return dp[k][0] if rotations_needed == 0 else dp[k][1]