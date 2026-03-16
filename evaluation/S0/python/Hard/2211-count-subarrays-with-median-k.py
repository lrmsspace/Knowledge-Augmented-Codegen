# Source: https://leetcode.com/problems/count-subarrays-with-median-k/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of size n consisting of distinct integers from 1 to n and a positive integer k.
#
# Return the number of non-empty subarrays in nums that have a median equal to k.
#
# Note:
#
#
# 	The median of an array is the middle element after sorting the array in ascending order. If the array is of even length, the median is the left middle element.
#
# 	
# 		For example, the median of [2,3,1,4] is 2, and the median of [8,4,3,5,1] is 4.
# 	
# 	
# 	A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [3,2,1,4,5], k = 4
# Output: 3
# Explanation: The subarrays that have a median equal to 4 are: [4], [4,5] and [1,4,5].
#
# Constraints:
# n == nums.length
# 	1 <= n <= 105
# 	1 <= nums[i], k <= n
# 	The integers in nums are distinct.
#

class Solution(object):
    def countSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        k_index = nums.index(k)

        balance_count = {0: 1}
        balance = 0

        for i in range(k_index - 1, -1, -1):
            if nums[i] < k:
                balance -= 1
            else:
                balance += 1
            balance_count[balance] = balance_count.get(balance, 0) + 1

        result = 0
        balance = 0

        for i in range(k_index, n):
            if nums[i] < k:
                balance -= 1
            else:
                balance += 1
            result += balance_count.get(-balance, 0)
            result += balance_count.get(-balance + 1, 0)

        return result   