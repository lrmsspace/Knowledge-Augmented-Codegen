# Source: https://leetcode.com/problems/sum-of-subarray-minimums/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
#
# Example:
# Input: arr = [3,1,2,4]
# Output: 17
# Explanation: 
# Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
# Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
# Sum is 17.
#
# Constraints:
# 1 <= arr.length <= 3 * 104
# 	1 <= arr[i] <= 3 * 104
#

class Solution(object):
    def sumSubarrayMins(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        stack = []
        result = 0
        prev_less = [-1] * len(arr)
        next_less = [len(arr)] * len(arr)

        for i in range(len(arr)):
            while stack and arr[stack[-1]] > arr[i]:
                next_less[stack.pop()] = i
            stack.append(i)

        stack.clear()

        for i in range(len(arr) - 1, -1, -1):
            while stack and arr[stack[-1]] >= arr[i]:
                prev_less[stack.pop()] = i
            stack.append(i)

        for i in range(len(arr)):
            left_count = i - prev_less[i]
            right_count = next_less[i] - i
            result += arr[i] * left_count * right_count
            result %= MOD

        return result