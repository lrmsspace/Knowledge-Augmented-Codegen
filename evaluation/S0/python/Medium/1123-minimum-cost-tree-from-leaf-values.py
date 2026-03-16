# Source: https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/   |   Difficulty: Medium
#
# Problem Description:
# Given an array arr of positive integers, consider all binary trees such that:
#
#
# 	Each node has either 0 or 2 children;
# 	The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
# 	The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
#
#
# Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.
#
# A node is a leaf if and only if it has zero children.
#
# Example:
# Input: arr = [6,2,4]
# Output: 32
# Explanation: There are two possible trees shown.
# The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.
#
# Constraints:
# 2 <= arr.length <= 40
# 	1 <= arr[i] <= 15
# 	It is guaranteed that the answer fits into a 32-bit signed integer (i.e., it is less than 231).
#

class Solution(object):
    def mctFromLeafValues(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        dp = [[0] * n for _ in range(n)]
        max_leaf = [[0] * n for _ in range(n)]

        for i in range(n):
            max_leaf[i][i] = arr[i]

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                dp[i][j] = float('inf')
                for k in range(i, j):
                    max_leaf[i][j] = max(max_leaf[i][j], max_leaf[i][k], max_leaf[k + 1][j])
                    cost = dp[i][k] + dp[k + 1][j] + max_leaf[i][k] * max_leaf[k + 1][j]
                    dp[i][j] = min(dp[i][j], cost)

        return dp[0][n - 1]