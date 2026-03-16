# Source: https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.
#
# A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.
#
# Example:
# Input: nums = [3,4,5,1,2]
# Output: 2
# Explanation: 
# After the first right shift, nums = [2,3,4,5,1].
# After the second right shift, nums = [1,2,3,4,5].
# Now nums is sorted; therefore the answer is 2.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
# 	nums contains distinct integers.
#

class Solution(object):
    def minimumRightShifts(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        count = 0
        for i in range(1, n):
            if nums[i] < nums[i - 1]:
                count += 1
                if count > 1:
                    return -1
                shift_index = i
        if count == 0:
            return 0
        if nums[0] < nums[-1]:
            return -1
        return n - shift_index