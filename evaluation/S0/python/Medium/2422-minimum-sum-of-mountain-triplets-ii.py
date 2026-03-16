# Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums of integers.
#
# A triplet of indices (i, j, k) is a mountain if:
#
#
# 	i < j < k
# 	nums[i] < nums[j] and nums[k] < nums[j]
#
#
# Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
#
# Example:
# Input: nums = [8,6,1,5,3]
# Output: 9
# Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
# - 2 < 3 < 4
# - nums[2] < nums[3] and nums[4] < nums[3]
# And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
#
# Constraints:
# 3 <= nums.length <= 105
# 	1 <= nums[i] <= 108
#

class Solution(object):
    def minimumSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left_min = [float('inf')] * n
        right_min = [float('inf')] * n

        stack = []
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                left_min[i] = nums[stack[-1]]
            stack.append(i)

        stack = []
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                right_min[i] = nums[stack[-1]]
            stack.append(i)

        min_sum = float('inf')
        for i in range(n):
            if left_min[i] != float('inf') and right_min[i] != float('inf'):
                min_sum = min(min_sum, left_min[i] + nums[i] + right_min[i])

        return min_sum if min_sum != float('inf') else -1