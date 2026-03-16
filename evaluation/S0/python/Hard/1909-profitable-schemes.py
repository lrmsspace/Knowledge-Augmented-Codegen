# Source: https://leetcode.com/problems/profitable-schemes/   |   Difficulty: Hard
#
# Problem Description:
# There is a group of n members, and a list of various crimes they could commit. The ith crime generates a profit[i] and requires group[i] members to participate in it. If a member participates in one crime, that member can't participate in another crime.
#
# Let's call a profitable scheme any subset of these crimes that generates at least minProfit profit, and the total number of members participating in that subset of crimes is at most n.
#
# Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
# Output: 2
# Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
# In total, there are 2 schemes.
#
# Constraints:
# 1 <= n <= 100
# 	0 <= minProfit <= 100
# 	1 <= group.length <= 100
# 	1 <= group[i] <= 100
# 	profit.length == group.length
# 	0 <= profit[i] <= 100
#

class Solution(object):
    def profitableSchemes(self, n, minProfit, group, profit):
        """
        :type n: int
        :type minProfit: int
        :type group: List[int]
        :type profit: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        m = len(group)
        
        # dp[i][j][k]: 前i个犯罪，使用j个人，获得至少k利润的方案数
        dp = [[[0] * (minProfit + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        
        # 初始化：不犯罪时，利润为0的方案数为1
        for j in range(n + 1):
            dp[0][j][0] = 1
        
        for i in range(1, m + 1):
            g = group[i - 1]
            p = profit[i - 1]
            for j in range(n + 1):
                for k in range(minProfit + 1):
                    # 不参与第i个犯罪
                    dp[i][j][k] = dp[i - 1][j][k]
                    
                    # 参与第i个犯罪
                    if j >= g:
                        dp[i][j][k] += dp[i - 1][j - g][max(0, k - p)]
                        dp[i][j][k] %= MOD
        
        return dp[m][n][minProfit]