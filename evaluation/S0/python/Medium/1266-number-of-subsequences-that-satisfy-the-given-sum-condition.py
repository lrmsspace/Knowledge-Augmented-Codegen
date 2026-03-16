# Source: https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of integers nums and an integer target.
#
# Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [3,5,6,7], target = 9
# Output: 4
# Explanation: There are 4 subsequences that satisfy the condition.
# [3] -> Min value + max value <= target (3 + 3 <= 9)
# [3,5] -> (3 + 5 <= 9)
# [3,5,6] -> (3 + 6 <= 9)
# [3,6] -> (3 + 6 <= 9)
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
# 	1 <= target <= 106
#

class Solution(object):
    def numSubseq(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        MOD = 10**9 + 7
        nums.sort()
        left, right = 0, len(nums) - 1
        result = 0
        pow2 = [1] * (len(nums) + 1)
        
        for i in range(1, len(nums) + 1):
            pow2[i] = (pow2[i - 1] * 2) % MOD
        
        while left <= right:
            if nums[left] + nums[right] <= target:
                result = (result + pow2[right - left]) % MOD
                left += 1
            else:
                right -= 1
        
        return result