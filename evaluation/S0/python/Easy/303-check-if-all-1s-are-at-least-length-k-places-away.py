# Source: https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/   |   Difficulty: Easy
#
# Problem Description:
# Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.
#
# Example:
# Input: nums = [1,0,0,0,1,0,0,1], k = 2
# Output: true
# Explanation: Each of the 1s are at least 2 places away from each other.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= k <= nums.length
# 	nums[i] is 0 or 1
#

class Solution(object):
    def kLengthApart(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        last_one_index = -k - 1  # Initialize to -k-1 to handle the first 1 correctly
        for i in range(len(nums)):
            if nums[i] == 1:
                if i - last_one_index <= k:
                    return False
                last_one_index = i
        return True