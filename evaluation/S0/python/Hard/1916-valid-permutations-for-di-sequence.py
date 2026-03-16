# Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s of length n where s[i] is either:
#
#
# 	'D' means decreasing, or
# 	'I' means increasing.
#
#
# A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
#
#
# 	If s[i] == 'D', then perm[i] > perm[i + 1], and
# 	If s[i] == 'I', then perm[i] < perm[i + 1].
#
#
# Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: s = "DID"
# Output: 5
# Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
# (1, 0, 3, 2)
# (2, 0, 3, 1)
# (2, 1, 3, 0)
# (3, 0, 2, 1)
# (3, 1, 2, 0)
#
# Constraints:
# n == s.length
# 	1 <= n <= 200
# 	s[i] is either 'I' or 'D'.
#

class Solution(object):
    def numPermsDISequence(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        MOD = 10**9 + 7

        # dp[i][j]: the number of valid permutations of length i+1 with the last number being j
        dp = [[0] * (n + 1) for _ in range(n + 1)]
        
        # Base case: for length 1, there's only one permutation for each last number
        for j in range(n + 1):
            dp[0][j] = 1

        for i in range(1, n + 1):
            if s[i - 1] == 'I':
                # If 'I', we can place numbers less than j at position i
                for j in range(i + 1):
                    dp[i][j] = sum(dp[i - 1][k] for k in range(j)) % MOD
            else:
                # If 'D', we can place numbers greater than j at position i
                for j in range(i + 1):
                    dp[i][j] = sum(dp[i - 1][k] for k in range(j, i)) % MOD

        return sum(dp[n - 1][j] for j in range(n + 1)) % MOD