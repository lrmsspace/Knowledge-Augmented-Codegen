# Source: https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. A number x is lonely when it appears only once, and no adjacent numbers (i.e. x + 1 and x - 1) appear in the array.
#
# Return all lonely numbers in nums. You may return the answer in any order.
#
# Example:
# Input: nums = [10,6,5,8]
# Output: [10,8]
# Explanation: 
# - 10 is a lonely number since it appears exactly once and 9 and 11 does not appear in nums.
# - 8 is a lonely number since it appears exactly once and 7 and 9 does not appear in nums.
# - 5 is not a lonely number since 6 appears in nums and vice versa.
# Hence, the lonely numbers in nums are [10, 8].
# Note that [8, 10] may also be returned.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 106
#

class Solution(object):
    def findLonely(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        num_set = set(nums)
        lonely_numbers = []

        for num in nums:
            if (num not in lonely_numbers and
                nums.count(num) == 1 and
                (num - 1) not in num_set and
                (num + 1) not in num_set):
                lonely_numbers.append(num)

        return lonely_numbers