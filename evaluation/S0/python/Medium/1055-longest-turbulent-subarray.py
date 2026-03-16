# Source: https://leetcode.com/problems/longest-turbulent-subarray/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, return the length of a maximum size turbulent subarray of arr.
#
# A subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
#
# More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]] of arr is said to be turbulent if and only if:
#
#
# 	For i <= k < j:
#
# 	
# 		arr[k] > arr[k + 1] when k is odd, and
# 		arr[k] < arr[k + 1] when k is even.
# 	
# 	
# 	Or, for i <= k < j:
# 	
# 		arr[k] > arr[k + 1] when k is even, and
# 		arr[k] < arr[k + 1] when k is odd.
#
# Example:
# Input: arr = [9,4,2,10,7,8,8,1,9]
# Output: 5
# Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
#
# Constraints:
# 1 <= arr.length <= 4 * 104
# 	0 <= arr[i] <= 109
#

class Solution(object):
    def maxTurbulenceSize(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        if n == 1:
            return 1
        
        inc = [1] * n
        dec = [1] * n
        
        for i in range(1, n):
            if arr[i] > arr[i - 1]:
                inc[i] = dec[i - 1] + 1
            elif arr[i] < arr[i - 1]:
                dec[i] = inc[i - 1] + 1
        
        return max(max(inc), max(dec))