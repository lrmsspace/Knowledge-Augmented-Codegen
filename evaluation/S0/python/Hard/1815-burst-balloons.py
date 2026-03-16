# Source: https://leetcode.com/problems/burst-balloons/   |   Difficulty: Hard
#
# Problem Description:
# You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
#
# If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
#
# Return the maximum coins you can collect by bursting the balloons wisely.
#
# Example:
# Input: nums = [3,1,5,8]
# Output: 167
# Explanation:
# nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
# coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
#
# Constraints:
# n == nums.length
# 	1 <= n <= 300
# 	0 <= nums[i] <= 100
#

class Solution(object):
    def maxCoins(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        # 在两端添加虚拟气球，方便计算
        nums = [1] + nums + [1]
        # dp[i][j]表示在开区间(i, j)内戳破所有气球能获得的最大硬币数
        dp = [[0] * (n + 2) for _ in range(n + 2)]

        # 枚举区间长度
        for length in range(2, n + 2):
            # 枚举区间起点
            for left in range(0, n + 2 - length):
                right = left + length
                # 枚举最后一个被戳破的气球位置
                for k in range(left + 1, right):
                    dp[left][right] = max(dp[left][right],
                                          dp[left][k] + dp[k][right] + nums[left] * nums[k] * nums[right])

        return dp[0][n + 1]