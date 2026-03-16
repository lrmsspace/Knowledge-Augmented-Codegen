# Source: https://leetcode.com/problems/jump-game-vii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:
#
#
# 	i + minJump <= j <= min(i + maxJump, s.length - 1), and
# 	s[j] == '0'.
#
#
# Return true if you can reach index s.length - 1 in s, or false otherwise.
#
# Example:
# Input: s = "011010", minJump = 2, maxJump = 3
# Output: true
# Explanation:
# In the first step, move from index 0 to index 3. 
# In the second step, move from index 3 to index 5.
#
# Constraints:
# 2 <= s.length <= 105
# 	s[i] is either '0' or '1'.
# 	s[0] == '0'
# 	1 <= minJump <= maxJump < s.length
#

class Solution(object):
    def canReach(self, s, minJump, maxJump):
        """
        :type s: str
        :type minJump: int
        :type maxJump: int
        :rtype: bool
        """
        n = len(s)
        dp = [False] * n
        dp[0] = True
        preSum = [0] * (n + 1)
        preSum[1] = 1  # preSum[i] 表示 dp[0..i-1] 中 True 的数量

        for i in range(1, n):
            if s[i] == '0':
                left = max(0, i - maxJump)
                right = i - minJump
                if right >= 0 and preSum[right + 1] - preSum[left] > 0:
                    dp[i] = True
            preSum[i + 1] = preSum[i] + (1 if dp[i] else 0)

        return dp[-1]