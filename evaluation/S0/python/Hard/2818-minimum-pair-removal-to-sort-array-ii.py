# Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given an array nums, you can perform the following operation any number of times:
#
#
# 	Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
# 	Replace the pair with their sum.
#
#
# Return the minimum number of operations needed to make the array non-decreasing.
#
# An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
#
# Example:
# Input: nums = [5,2,3,1]
#
# Output: 2
#
# Explanation:
#
#
# 	The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
# 	The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
#
#
# The array nums became non-decreasing in two operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def minimumPairRemoval(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n <= 1:
            return 0

        removals = 0
        while True:
            is_sorted = True
            for i in range(1, len(nums)):
                if nums[i] < nums[i - 1]:
                    is_sorted = False
                    break
            if is_sorted:
                break

            min_sum = float('inf')
            min_index = -1
            for i in range(len(nums) - 1):
                pair_sum = nums[i] + nums[i + 1]
                if pair_sum < min_sum:
                    min_sum = pair_sum
                    min_index = i

            nums[min_index] = min_sum
            del nums[min_index + 1]
            removals += 1

        return removals