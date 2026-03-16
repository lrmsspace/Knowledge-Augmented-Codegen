# Source: https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/   |   Difficulty: Hard
#
# Problem Description:
# Given n orders, each order consists of a pickup and a delivery service.
#
# Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i). 
#
# Since the answer may be too large, return it modulo 10^9 + 7.
#
# Example:
# Input: n = 1
# Output: 1
# Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
#
# Constraints:
# 1 <= n <= 500
#

class Solution(object):
    def countOrders(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        res = 1
        for i in range(1, n + 1):
            res = res * i * (2 * i - 1) % MOD
        return res