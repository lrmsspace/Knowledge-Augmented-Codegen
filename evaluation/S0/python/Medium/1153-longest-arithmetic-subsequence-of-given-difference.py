# Source: https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.
#
# A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: arr = [1,2,3,4], difference = 1
# Output: 4
# Explanation: The longest arithmetic subsequence is [1,2,3,4].
#
# Constraints:
# 1 <= arr.length <= 105
# 	-104 <= arr[i], difference <= 104
#

class Solution(object):
    def longestSubsequence(self, arr, difference):
        """
        :type arr: List[int]
        :type difference: int
        :rtype: int
        """
        dp = {}
        max_length = 0
        
        for num in arr:
            prev_num = num - difference
            if prev_num in dp:
                dp[num] = dp[prev_num] + 1
            else:
                dp[num] = 1
            
            max_length = max(max_length, dp[num])
        
        return max_length