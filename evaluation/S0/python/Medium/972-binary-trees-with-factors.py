# Source: https://leetcode.com/problems/binary-trees-with-factors/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
#
# We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
#
# Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
#
# Example:
# Input: arr = [2,4]
# Output: 3
# Explanation: We can make these trees: [2], [4], [4, 2, 2]
#
# Constraints:
# 1 <= arr.length <= 1000
# 	2 <= arr[i] <= 109
# 	All the values of arr are unique.
#

class Solution(object):
    def numFactoredBinaryTrees(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        arr.sort()
        dp = {}
        
        for x in arr:
            dp[x] = 1  # 每个数字本身可以作为一个单节点树
        
        for i in range(len(arr)):
            for j in range(i):
                if arr[i] % arr[j] == 0:  # arr[j] 是 arr[i] 的一个因子
                    right = arr[i] // arr[j]
                    if right in dp:
                        dp[arr[i]] += dp[arr[j]] * dp[right]
                        dp[arr[i]] %= MOD
        
        return sum(dp.values()) % MOD