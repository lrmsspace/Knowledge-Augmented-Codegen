# Source: https://leetcode.com/problems/consecutive-numbers-sum/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.
#
# Example:
# Input: n = 5
# Output: 2
# Explanation: 5 = 2 + 3
#
# Constraints:
# 1 <= n <= 109
#

class Solution(object):
    def consecutiveNumbersSum(self, n):
        """
        :type n: int
        :rtype: int
        """
        count = 0
        for k in range(1, n + 1):
            # Calculate the sum of the first k-1 integers
            sum_k_minus_1 = (k - 1) * k // 2
            if n - sum_k_minus_1 <= 0:
                break
            if (n - sum_k_minus_1) % k == 0:
                count += 1
        return count