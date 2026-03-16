# Source: https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/   |   Difficulty: Easy
#
# Problem Description:
# In the town of Digitville, there was a list of numbers called nums containing integers from 0 to n - 1. Each number was supposed to appear exactly once in the list, however, two mischievous numbers sneaked in an additional time, making the list longer than usual.
#
# As the town detective, your task is to find these two sneaky numbers. Return an array of size two containing the two numbers (in any order), so peace can return to Digitville.
#
# Example:
# Input: nums = [0,1,1,0]
#
# Output: [0,1]
#
# Explanation:
#
# The numbers 0 and 1 each appear twice in the array.
#
# Constraints:
# 2 <= n <= 100
# 	nums.length == n + 2
# 	0 <= nums[i] < n
# 	The input is generated such that nums contains exactly two repeated elements.
#

class Solution(object):
    def getSneakyNumbers(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        seen = set()
        sneaky_numbers = []

        for num in nums:
            if num in seen:
                sneaky_numbers.append(num)
            else:
                seen.add(num)

        return sneaky_numbers