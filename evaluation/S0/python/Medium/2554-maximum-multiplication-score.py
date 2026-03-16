# Source: https://leetcode.com/problems/maximum-multiplication-score/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array a of size 4 and another integer array b of size at least 4.
#
# You need to choose 4 indices i0, i1, i2, and i3 from the array b such that i0 < i1 < i2 < i3. Your score will be equal to the value a[0] * b[i0] + a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3].
#
# Return the maximum score you can achieve.
#
# Example:
# Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
#
# Output: 26
#
# Explanation:
# We can choose the indices 0, 1, 2, and 5. The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.
#
# Constraints:
# a.length == 4
# 	4 <= b.length <= 105
# 	-105 <= a[i], b[i] <= 105
#

class Solution(object):
    def maxScore(self, a, b):
        """
        :type a: List[int]
        :type b: List[int]
        :rtype: int
        """
        n = len(b)
        dp = [[float('-inf')] * 4 for _ in range(n + 1)]
        
        for i in range(n + 1):
            dp[i][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, 5):
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[j - 1] * b[i - 1])
        
        return dp[n][4]