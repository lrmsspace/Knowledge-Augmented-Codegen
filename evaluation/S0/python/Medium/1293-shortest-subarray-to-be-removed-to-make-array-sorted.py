# Source: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
#
# Return the length of the shortest subarray to remove.
#
# A subarray is a contiguous subsequence of the array.
#
# Example:
# Input: arr = [1,2,3,10,4,2,3,5]
# Output: 3
# Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
# Another correct solution is to remove the subarray [3,10,4].
#
# Constraints:
# 1 <= arr.length <= 105
# 	0 <= arr[i] <= 109
#

class Solution(object):
    def findLengthOfShortestSubarray(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        left = 0
        while left + 1 < n and arr[left] <= arr[left + 1]:
            left += 1
        
        if left == n - 1:
            return 0
        
        right = n - 1
        while right - 1 >= 0 and arr[right - 1] <= arr[right]:
            right -= 1
        
        res = min(n - left - 1, right)
        
        i = 0
        j = right
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                res = min(res, j - i - 1)
                i += 1
            else:
                j += 1
        
        return res