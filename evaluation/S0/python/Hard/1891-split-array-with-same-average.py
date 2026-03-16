# Source: https://leetcode.com/problems/split-array-with-same-average/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).
#
# Return true if it is possible to achieve that and false otherwise.
#
# Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.
#
# Example:
# Input: nums = [1,2,3,4,5,6,7,8]
# Output: true
# Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
#
# Constraints:
# 1 <= nums.length <= 30
# 	0 <= nums[i] <= 104
#

class Solution(object):
    def splitArraySameAverage(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        from itertools import combinations

        n = len(nums)
        total_sum = sum(nums)

        for size in range(1, n // 2 + 1):
            if (total_sum * size) % n != 0:
                continue
            target_sum = (total_sum * size) // n
            for combo in combinations(nums, size):
                if sum(combo) == target_sum:
                    return True
        return False