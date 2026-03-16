# Source: https://leetcode.com/problems/unique-binary-search-trees/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.
#
# Example:
# Input: n = 3
# Output: 5
#
# Constraints:
# 1 <= n <= 19
#

class Solution(object):
    def numTrees(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [0] * (n + 1)
        dp[0] = 1  # An empty tree
        dp[1] = 1  # A single node tree

        for nodes in range(2, n + 1):
            for root in range(1, nodes + 1):
                left = root - 1          # Number of nodes in the left subtree
                right = nodes - root     # Number of nodes in the right subtree
                dp[nodes] += dp[left] * dp[right]

        return dp[n]