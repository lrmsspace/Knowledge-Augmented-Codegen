# Source: https://leetcode.com/problems/sum-of-all-odd-length-subarrays/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.
#
# A subarray is a contiguous subsequence of the array.
#
# Example:
# Input: arr = [1,4,2,5,3]
# Output: 58
# Explanation: The odd-length subarrays of arr and their sums are:
# [1] = 1
# [4] = 4
# [2] = 2
# [5] = 5
# [3] = 3
# [1,4,2] = 7
# [4,2,5] = 11
# [2,5,3] = 10
# [1,4,2,5,3] = 15
# If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
#
# Constraints:
# 1 <= arr.length <= 100
# 	1 <= arr[i] <= 1000
#
#
#  
# Follow up:
#
# Could you solve this problem in O(n) time complexity?
#

class Solution(object):
    def sumOddLengthSubarrays(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        total_sum = 0
        
        for i in range(n):
            # Calculate the number of subarrays that include arr[i]
            left_count = i + 1
            right_count = n - i
            
            # Total subarrays including arr[i]
            total_subarrays = left_count * right_count
            
            # Odd-length subarrays including arr[i]
            odd_subarrays = (total_subarrays + 1) // 2
            
            # Contribution of arr[i] to the total sum
            total_sum += arr[i] * odd_subarrays
            
        return total_sum