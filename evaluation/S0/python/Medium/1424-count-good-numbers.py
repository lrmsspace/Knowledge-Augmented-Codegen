# Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
#
# Problem Description:
# A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
#
#
# 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
#
#
# Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
#
# A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
#
# Constraints:
# 1 <= n <= 1015
#

class Solution(object):
    def countGoodNumbers(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        even_positions = (n + 1) // 2  # Number of even indices
        odd_positions = n // 2          # Number of odd indices
        
        # Calculate the number of choices for even and odd positions
        even_choices = pow(5, even_positions, MOD)  # Digits: 0, 2, 4, 6, 8
        odd_choices = pow(4, odd_positions, MOD)    # Digits: 2, 3, 5, 7
        
        # Total good numbers is the product of choices for even and odd positions
        return (even_choices * odd_choices) % MOD