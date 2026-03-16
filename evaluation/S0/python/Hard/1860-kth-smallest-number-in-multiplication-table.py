# Source: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/   |   Difficulty: Hard
#
# Problem Description:
# Nearly everyone has used the Multiplication Table. The multiplication table of size m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed).
#
# Given three integers m, n, and k, return the kth smallest element in the m x n multiplication table.
#
# Example:
# Input: m = 3, n = 3, k = 5
# Output: 3
# Explanation: The 5th smallest number is 3.
#
# Constraints:
# 1 <= m, n <= 3 * 104
# 	1 <= k <= m * n
#

class Solution(object):
    def findKthNumber(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        left, right = 1, m * n
        while left < right:
            mid = (left + right) // 2
            count = sum(min(mid // i, n) for i in range(1, m + 1))
            if count < k:
                left = mid + 1
            else:
                right = mid
        return left