# Source: https://leetcode.com/problems/target-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer target.
#
# You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
#
#
# 	For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
#
#
# Return the number of different expressions that you can build, which evaluates to target.
#
# Example:
# Input: nums = [1,1,1,1,1], target = 3
# Output: 5
# Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
# -1 + 1 + 1 + 1 + 1 = 3
# +1 - 1 + 1 + 1 + 1 = 3
# +1 + 1 - 1 + 1 + 1 = 3
# +1 + 1 + 1 - 1 + 1 = 3
# +1 + 1 + 1 + 1 - 1 = 3
#
# Constraints:
# 1 <= nums.length <= 20
# 	0 <= nums[i] <= 1000
# 	0 <= sum(nums[i]) <= 1000
# 	-1000 <= target <= 1000
#

class Solution(object):
    def findTargetSumWays(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        total = sum(nums)
        if (total + target) % 2 != 0 or total < abs(target):
            return 0
        subset_sum = (total + target) // 2
        
        dp = [0] * (subset_sum + 1)
        dp[0] = 1
        
        for num in nums:
            for j in range(subset_sum, num - 1, -1):
                dp[j] += dp[j - num]
        
        return dp[subset_sum]