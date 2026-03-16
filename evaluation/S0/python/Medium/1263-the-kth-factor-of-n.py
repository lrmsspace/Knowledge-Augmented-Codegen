# Source: https://leetcode.com/problems/the-kth-factor-of-n/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers n and k. A factor of an integer n is defined as an integer i where n % i == 0.
#
# Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
#
# Example:
# Input: n = 12, k = 3
# Output: 3
# Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
#
# Constraints:
# 1 <= k <= n <= 1000
#
#
#  
# Follow up:
#
# Could you solve this problem in less than O(n) complexity?
#

class Solution(object):
    def kthFactor(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        factors = []
        for i in range(1, n + 1):
            if n % i == 0:
                factors.append(i)
            if len(factors) == k:
                return factors[-1]
        return -1