# Source: https://leetcode.com/problems/previous-permutation-with-one-swap/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, that can be made with exactly one swap. If it cannot be done, then return the same array.
#
# Note that a swap exchanges the positions of two numbers arr[i] and arr[j]
#
# Example:
# Input: arr = [3,2,1]
# Output: [3,1,2]
# Explanation: Swapping 2 and 1.
#
# Constraints:
# 1 <= arr.length <= 104
# 	1 <= arr[i] <= 104
#

class Solution(object):
    def prevPermOpt1(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        n = len(arr)
        i = n - 2
        
        # Step 1: Find the first decreasing element from the right
        while i >= 0 and arr[i] <= arr[i + 1]:
            i -= 1
        
        if i == -1:
            return arr  # The array is already the smallest permutation
        
        # Step 2: Find the largest element to the right of arr[i] that is smaller than arr[i]
        j = n - 1
        while arr[j] >= arr[i] or (j < n - 1 and arr[j] == arr[j + 1]):
            j -= 1
        
        # Step 3: Swap arr[i] and arr[j]
        arr[i], arr[j] = arr[j], arr[i]
        
        return arr