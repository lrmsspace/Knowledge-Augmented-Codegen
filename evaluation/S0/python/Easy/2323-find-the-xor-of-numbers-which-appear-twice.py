# Source: https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array nums, where each number in the array appears either once or twice.
#
# Return the bitwise XOR of all the numbers that appear twice in the array, or 0 if no number appears twice.
#
# Example:
# Input: nums = [1,2,1,3]
#
# Output: 1
#
# Explanation:
#
# The only number that appears twice in nums is 1.
#
# Constraints:
# 1 <= nums.length <= 50
# 	1 <= nums[i] <= 50
# 	Each number in nums appears either once or twice.
#

class Solution(object):
    def duplicateNumbersXOR(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        num_count = {}
        xor_result = 0
        
        for num in nums:
            if num in num_count:
                num_count[num] += 1
            else:
                num_count[num] = 1
        
        for num, count in num_count.items():
            if count == 2:
                xor_result ^= num
        
        return xor_result