# Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
#
# Problem Description:
# Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
#
# In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
#
# If there is no way to make arr1 strictly increasing, return -1.
#
# Example:
# Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
# Output: 1
# Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
#
# Constraints:
# 1 <= arr1.length, arr2.length <= 2000
# 	0 <= arr1[i], arr2[i] <= 10^9
#

class Solution(object):
    def makeArrayIncreasing(self, arr1, arr2):
        """
        :type arr1: List[int]
        :type arr2: List[int]
        :rtype: int
        """
        from bisect import bisect_right
        arr2 = sorted(set(arr2))
        n = len(arr1)
        dp = { -1: 0 }
        
        for i in range(n):
            new_dp = {}
            for key in dp:
                if arr1[i] > key:
                    new_dp[arr1[i]] = min(new_dp.get(arr1[i], float('inf')), dp[key])
                
                idx = bisect_right(arr2, key)
                if idx < len(arr2):
                    new_dp[arr2[idx]] = min(new_dp.get(arr2[idx], float('inf')), dp[key] + 1)
            
            dp = new_dp
            if not dp:
                return -1
        
        return min(dp.values())