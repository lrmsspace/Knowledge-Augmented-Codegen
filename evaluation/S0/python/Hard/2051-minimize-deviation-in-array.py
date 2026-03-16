# Source: https://leetcode.com/problems/minimize-deviation-in-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n positive integers.
#
# You can perform two types of operations on any element of the array any number of times:
#
#
# 	If the element is even, divide it by 2.
#
# 	
# 		For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
# 	
# 	
# 	If the element is odd, multiply it by 2.
# 	
# 		For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
# 	
# 	
#
#
# The deviation of the array is the maximum difference between any two elements in the array.
#
# Return the minimum deviation the array can have after performing some number of operations.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 1
# Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 5 * 104
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def minimumDeviation(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        import heapq

        # Step 1: Normalize the array by making all numbers even
        max_heap = []
        min_num = float('inf')

        for num in nums:
            if num % 2 == 1:
                num *= 2
            heapq.heappush(max_heap, -num)
            min_num = min(min_num, num)

        # Step 2: Calculate the minimum deviation
        min_deviation = float('inf')

        while True:
            max_num = -heapq.heappop(max_heap)
            min_deviation = min(min_deviation, max_num - min_num)

            if max_num % 2 == 0:
                new_num = max_num // 2
                min_num = min(min_num, new_num)
                heapq.heappush(max_heap, -new_num)
            else:
                break

        return min_deviation