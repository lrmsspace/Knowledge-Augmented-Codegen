# Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
#
# The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: arr = [0]
# Output: 1
# Explanation: There is only one possible result: 0.
#
# Constraints:
# 1 <= arr.length <= 5 * 104
# 	0 <= arr[i] <= 109
#

class Solution(object):
    def subarrayBitwiseORs(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        result = set()
        current = set()
        
        for num in arr:
            current = {num | x for x in current} | {num}
            result |= current
            
        return len(result)