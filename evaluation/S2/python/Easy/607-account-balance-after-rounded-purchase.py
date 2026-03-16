# Source: https://leetcode.com/problems/account-balance-after-rounded-purchase/   |   Difficulty: Easy
#
# Problem Description:
# Initially, you have a bank account balance of 100 dollars.
#
# You are given an integer purchaseAmount representing the amount you will spend on a purchase in dollars, in other words, its price.
#
# When making the purchase, first the purchaseAmount is rounded to the nearest multiple of 10. Let us call this value roundedAmount. Then, roundedAmount dollars are removed from your bank account.
#
# Return an integer denoting your final bank account balance after this purchase.
#
# Notes:
#
#
# 	0 is considered to be a multiple of 10 in this problem.
# 	When rounding, 5 is rounded upward (5 is rounded to 10, 15 is rounded to 20, 25 to 30, and so on).
#
# Example:
# Input: purchaseAmount = 9
#
# Output: 90
#
# Explanation:
#
# The nearest multiple of 10 to 9 is 10. So your account balance becomes 100 - 10 = 90.
#
# Constraints:
# 0 <= purchaseAmount <= 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def accountBalanceAfterPurchase(self, purchaseAmount):
        """
        :type purchaseAmount: int
        :rtype: int
        """
        roundedAmount = ((purchaseAmount + 5) // 10) * 10
        return 100 - roundedAmount