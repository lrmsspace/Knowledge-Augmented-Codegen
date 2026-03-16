# Source: https://leetcode.com/problems/longest-consecutive-sequence/   |   Difficulty: Medium
#
# Problem Description:
# Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
#
# You must write an algorithm that runs in O(n) time.
#
# Example:
# Input: nums = [100,4,200,1,3,2]
# Output: 4
# Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
#
# Constraints:
# 0 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def longestConsecutive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        num_set = set(nums)
        longest_streak = 0

        for num in num_set:
            if num - 1 not in num_set:  # only start counting if 'num' is the start of a sequence
                current_num = num
                current_streak = 1

                while current_num + 1 in num_set:
                    current_num += 1
                    current_streak += 1

                longest_streak = max(longest_streak, current_streak)

        return longest_streak