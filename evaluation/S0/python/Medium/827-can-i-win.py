# Source: https://leetcode.com/problems/can-i-win/   |   Difficulty: Medium
#
# Problem Description:
# In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.
#
# What if we change the game so that players cannot re-use integers?
#
# For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.
#
# Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise, return false. Assume both players play optimally.
#
# Example:
# Input: maxChoosableInteger = 10, desiredTotal = 11
# Output: false
# Explanation:
# No matter which integer the first player choose, the first player will lose.
# The first player can choose an integer from 1 up to 10.
# If the first player choose 1, the second player can only choose integers from 2 up to 10.
# The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
# Same with other integers chosen by the first player, the second player will always win.
#
# Constraints:
# 1 <= maxChoosableInteger <= 20
# 	0 <= desiredTotal <= 300
#

class Solution(object):
    def canIWin(self, maxChoosableInteger, desiredTotal):
        """
        :type maxChoosableInteger: int
        :type desiredTotal: int
        :rtype: bool
        """
        if desiredTotal <= 0:
            return True
        if (maxChoosableInteger * (maxChoosableInteger + 1)) // 2 < desiredTotal:
            return False

        memo = {}

        def can_win(used_numbers, current_total):
            if used_numbers in memo:
                return memo[used_numbers]

            for i in range(1, maxChoosableInteger + 1):
                current_bit = 1 << (i - 1)
                if used_numbers & current_bit == 0:
                    if current_total + i >= desiredTotal or not can_win(used_numbers | current_bit, current_total + i):
                        memo[used_numbers] = True
                        return True

            memo[used_numbers] = False
            return False

        return can_win(0, 0)