# Source: https://leetcode.com/problems/duplicate-zeros/   |   Difficulty: Easy
#
# Problem Description:
# Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
#
# Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.
#
# Example:
# Input: arr = [1,0,2,3,0,4,5,0]
# Output: [1,0,0,2,3,0,0,4]
# Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
#
# Constraints:
# 1 <= arr.length <= 104
# 	0 <= arr[i] <= 9
#

class Solution(object):
    def duplicateZeros(self, arr):
        """
        :type arr: List[int]
        :rtype: None Do not return anything, modify arr in-place instead.
        """
        n = len(arr)
        i = 0
        while i < n:
            if arr[i] == 0:
                arr.insert(i + 1, 0)  # Insert an additional zero
                arr.pop()  # Remove the last element to maintain the length
                i += 1  # Skip the next zero we just added
            i += 1