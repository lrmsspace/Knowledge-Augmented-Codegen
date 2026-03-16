# Source: https://leetcode.com/problems/continuous-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
#
#
# 	Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.
#
#
# Return the total number of continuous subarrays.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [5,4,2,4]
# Output: 8
# Explanation: 
# Continuous subarray of size 1: [5], [4], [2], [4].
# Continuous subarray of size 2: [5,4], [4,2], [2,4].
# Continuous subarray of size 3: [4,2,4].
# There are no subarrys of size 4.
# Total continuous subarrays = 4 + 3 + 1 = 8.
# It can be shown that there are no more continuous subarrays.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def continuousSubarrays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left = 0
        result = 0
        min_deque = []
        max_deque = []

        for right in range(n):
            while min_deque and nums[right] < min_deque[-1]:
                min_deque.pop()
            min_deque.append(nums[right])

            while max_deque and nums[right] > max_deque[-1]:
                max_deque.pop()
            max_deque.append(nums[right])

            while max_deque[0] - min_deque[0] > 2:
                if nums[left] == min_deque[0]:
                    min_deque.pop(0)
                if nums[left] == max_deque[0]:
                    max_deque.pop(0)
                left += 1

            result += right - left + 1

        return result