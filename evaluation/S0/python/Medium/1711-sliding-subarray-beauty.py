# Source: https://leetcode.com/problems/sliding-subarray-beauty/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums containing n integers, find the beauty of each subarray of size k.
#
# The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if there are fewer than x negative integers.
#
# Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays in order from the first index in the array.
#
#
# 	
# 	A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
# Output: [-1,-2,-2]
# Explanation: There are 3 subarrays with size k = 3. 
# The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
# The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
# The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.
#
# Constraints:
# n == nums.length 
# 	1 <= n <= 105
# 	1 <= k <= n
# 	1 <= x <= k 
# 	-50 <= nums[i] <= 50
#

class Solution(object):
    def getSubarrayBeauty(self, nums, k, x):
        """
        :type nums: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        from sortedcontainers import SortedList

        n = len(nums)
        result = []
        window = SortedList()

        for i in range(n):
            window.add(nums[i])

            if i >= k:
                window.remove(nums[i - k])

            if i >= k - 1:
                negatives = [num for num in window if num < 0]
                if len(negatives) < x:
                    result.append(0)
                else:
                    result.append(negatives[x - 1])

        return result