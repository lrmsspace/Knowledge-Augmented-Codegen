# Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and an integer goal.
#
# You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
#
# Return the minimum possible value of abs(sum - goal).
#
# Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
#
# Example:
# Input: nums = [5,-7,3,5], goal = 6
# Output: 0
# Explanation: Choose the whole array as a subsequence, with a sum of 6.
# This is equal to the goal, so the absolute difference is 0.
#
# Constraints:
# 1 <= nums.length <= 40
# 	-107 <= nums[i] <= 107
# 	-109 <= goal <= 109
#

class Solution(object):
    def minAbsDifference(self, nums, goal):
        """
        :type nums: List[int]
        :type goal: int
        :rtype: int
        """
        def compute_subsequence_sums(arr):
            sums = {0}
            for num in arr:
                new_sums = set()
                for s in sums:
                    new_sums.add(s + num)
                sums |= new_sums
            return sorted(sums)

        n = len(nums)
        left_sums = compute_subsequence_sums(nums[:n//2])
        right_sums = compute_subsequence_sums(nums[n//2:])

        min_diff = float('inf')
        j = len(right_sums) - 1

        for left_sum in left_sums:
            while j >= 0 and left_sum + right_sums[j] > goal:
                j -= 1

            if j >= 0:
                min_diff = min(min_diff, abs(left_sum + right_sums[j] - goal))
            if j + 1 < len(right_sums):
                min_diff = min(min_diff, abs(left_sum + right_sums[j + 1] - goal))

        return min_diff