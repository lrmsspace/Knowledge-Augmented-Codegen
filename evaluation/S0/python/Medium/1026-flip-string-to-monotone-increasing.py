# Source: https://leetcode.com/problems/flip-string-to-monotone-increasing/   |   Difficulty: Medium
#
# Problem Description:
# A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
#
# You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
#
# Return the minimum number of flips to make s monotone increasing.
#
# Example:
# Input: s = "00110"
# Output: 1
# Explanation: We flip the last digit to get 00111.
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minFlipsMonoIncr(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        dp = [0] * (n + 1)
        
        for i in range(1, n + 1):
            if s[i - 1] == '0':
                dp[i] = dp[i - 1]
            else:
                dp[i] = min(dp[i - 1] + 1, i - 1 - dp[i - 1])
        
        return dp[n]