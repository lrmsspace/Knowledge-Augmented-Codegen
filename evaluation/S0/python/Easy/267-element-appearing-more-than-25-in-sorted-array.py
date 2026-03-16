# Source: https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.
#
# Example:
# Input: arr = [1,2,2,6,6,6,6,7,10]
# Output: 6
#
# Constraints:
# 1 <= arr.length <= 104
# 	0 <= arr[i] <= 105
#

class Solution(object):
    def findSpecialInteger(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        count_threshold = n // 4
        
        current_num = arr[0]
        current_count = 1
        
        for i in range(1, n):
            if arr[i] == current_num:
                current_count += 1
                if current_count > count_threshold:
                    return current_num
            else:
                current_num = arr[i]
                current_count = 1
        
        return current_num  # The problem guarantees that there is always a valid answer