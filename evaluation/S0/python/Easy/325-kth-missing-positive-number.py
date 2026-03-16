# Source: https://leetcode.com/problems/kth-missing-positive-number/   |   Difficulty: Easy
#
# Problem Description:
# Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
#
# Return the kth positive integer that is missing from this array.
#
# Example:
# Input: arr = [2,3,4,7,11], k = 5
# Output: 9
# Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
#
# Constraints:
# 1 <= arr.length <= 1000
# 	1 <= arr[i] <= 1000
# 	1 <= k <= 1000
# 	arr[i] < arr[j] for 1 <= i < j <= arr.length
#
#
#  
# Follow up:
#
# Could you solve this problem in less than O(n) complexity?
#

class Solution(object):
    def findKthPositive(self, arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: int
        """
        missing_count = 0
        current = 1
        index = 0
        n = len(arr)
        
        while True:
            if index < n and arr[index] == current:
                index += 1
            else:
                missing_count += 1
                if missing_count == k:
                    return current
            current += 1