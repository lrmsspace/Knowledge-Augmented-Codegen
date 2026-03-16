# Source: https://leetcode.com/problems/minimum-money-required-before-transactions/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array transactions, where transactions[i] = [costi, cashbacki].
#
# The array describes transactions, where each transaction must be completed exactly once in some order. At any given moment, you have a certain amount of money. In order to complete transaction i, money >= costi must hold true. After performing a transaction, money becomes money - costi + cashbacki.
#
# Return the minimum amount of money required before any transaction so that all of the transactions can be completed regardless of the order of the transactions.
#
# Example:
# Input: transactions = [[2,1],[5,0],[4,2]]
# Output: 10
# Explanation:
# Starting with money = 10, the transactions can be performed in any order.
# It can be shown that starting with money < 10 will fail to complete all transactions in some order.
#
# Constraints:
# 1 <= transactions.length <= 105
# 	transactions[i].length == 2
# 	0 <= costi, cashbacki <= 109
#

class Solution(object):
    def minimumMoney(self, transactions):
        """
        :type transactions: List[List[int]]
        :rtype: int
        """
        need = 0
        extra = 0
        for cost, cashback in transactions:
            if cost > cashback:
                need += cost - cashback
            else:
                extra = max(extra, cost)
        return need + extra