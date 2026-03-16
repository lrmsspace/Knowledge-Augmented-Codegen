# Source: https://leetcode.com/problems/number-of-ways-to-separate-numbers/   |   Difficulty: Hard
#
# Problem Description:
# You wrote down many positive integers in a string called num. However, you realized that you forgot to add commas to seperate the different numbers. You remember that the list of integers was non-decreasing and that no integer had leading zeros.
#
# Return the number of possible lists of integers that you could have written down to get the string num. Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: num = "327"
# Output: 2
# Explanation: You could have written down the numbers:
# 3, 27
# 327
#
# Constraints:
# 1 <= num.length <= 3500
#  num consists of digits '0' through '9'.
#

class Solution(object):
    def numberOfCombinations(self, num):
        """
        :type num: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(num)
        
        if num[0] == '0':
            return 0
        
        # Precompute longest common prefix (LCP)
        lcp = [[0] * (n + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if num[i] == num[j]:
                    lcp[i][j] = lcp[i + 1][j + 1] + 1
        
        dp = [0] * (n + 1)
        dp[0] = 1
        
        for i in range(1, n + 1):
            if num[i - 1] == '0':
                continue
            
            for length in range(1, i + 1):
                j = i - length
                if j < 0:
                    break
                
                if j == 0:
                    dp[i] = (dp[i] + dp[j]) % MOD
                else:
                    prev_length = length
                    if j - prev_length < 0:
                        dp[i] = (dp[i] + dp[j]) % MOD
                    else:
                        cmp_index = j - prev_length
                        common_length = lcp[cmp_index][j]
                        if common_length >= prev_length or num[cmp_index + common_length] <= num[j + common_length]:
                            dp[i] = (dp[i] + dp[j]) % MOD
        
        return dp[n]