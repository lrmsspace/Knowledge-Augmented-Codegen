# Source: https://leetcode.com/problems/sorting-three-groups/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you can remove an element from nums. Return the minimum number of operations to make nums non-decreasing.
#
# Example:
# Input: nums = [2,1,3,2,1]
#
# Output: 3
#
# Explanation:
#
# One of the optimal solutions is to remove nums[0], nums[2] and nums[3].
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 3
#
#
#  
# Follow-up: Can you come up with an algorithm that runs in O(n) time complexity?
#

class Solution(object):
    def minimumOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [[float('inf')] * 4 for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, 4):
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + (nums[i - 1] != j))
        
        return min(dp[n])