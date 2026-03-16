# Source: https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.
#
# A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.
#
# Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false.
#
# Example:
# Input: arr = [1,2,4,4,4,4], m = 1, k = 3
# Output: true
# Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.
#
# Constraints:
# 2 <= arr.length <= 100
# 	1 <= arr[i] <= 100
# 	1 <= m <= 100
# 	2 <= k <= 100
#

class Solution(object):
    def containsPattern(self, arr, m, k):
        """
        :type arr: List[int]
        :type m: int
        :type k: int
        :rtype: bool
        """
        n = len(arr)
        for i in range(n - m * k + 1):
            pattern = arr[i:i + m]
            match = True
            for j in range(1, k):
                if arr[i + j * m:i + (j + 1) * m] != pattern:
                    match = False
                    break
            if match:
                return True
        return False