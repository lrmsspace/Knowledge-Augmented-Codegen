# Source: https://leetcode.com/problems/count-almost-equal-pairs-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# We call two integers x and y in this problem almost equal if both integers can become equal after performing the following operation at most once:
#
#
# 	Choose either x or y and swap any two digits within the chosen number.
#
#
# Return the number of indices i and j in nums where i < j such that nums[i] and nums[j] are almost equal.
#
# Note that it is allowed for an integer to have leading zeros after performing an operation.
#
# Example:
# Input: nums = [3,12,30,17,21]
#
# Output: 2
#
# Explanation:
#
# The almost equal pairs of elements are:
#
#
# 	3 and 30. By swapping 3 and 0 in 30, you get 3.
# 	12 and 21. By swapping 1 and 2 in 12, you get 21.
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def countPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        def get_signature(num):
            count = [0] * 10
            for digit in str(num):
                count[int(digit)] += 1
            return tuple(count)

        signature_map = defaultdict(int)
        for num in nums:
            signature = get_signature(num)
            signature_map[signature] += 1

        result = 0
        for count in signature_map.values():
            if count > 1:
                result += count * (count - 1) // 2

        return result