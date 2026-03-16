# Source: https://leetcode.com/problems/largest-divisible-subset/   |   Difficulty: Medium
#
# Problem Description:
# Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
#
#
# 	answer[i] % answer[j] == 0, or
# 	answer[j] % answer[i] == 0
#
#
# If there are multiple solutions, return any of them.
#
# Example:
# Input: nums = [1,2,3]
# Output: [1,2]
# Explanation: [1,3] is also accepted.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 2 * 109
# 	All the integers in nums are unique.
#

class Solution(object):
    def largestDivisibleSubset(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        nums.sort()
        n = len(nums)
        dp = [1] * n
        prev = [-1] * n

        max_size = 1
        max_index = 0

        for i in range(1, n):
            for j in range(i):
                if nums[i] % nums[j] == 0 and dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    prev[i] = j

            if dp[i] > max_size:
                max_size = dp[i]
                max_index = i

        result = []
        while max_index != -1:
            result.append(nums[max_index])
            max_index = prev[max_index]

        return result[::-1]