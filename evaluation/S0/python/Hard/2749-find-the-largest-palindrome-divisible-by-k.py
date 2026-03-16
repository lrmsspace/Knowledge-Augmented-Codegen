# Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers n and k.
#
# An integer x is called k-palindromic if:
#
#
# 	x is a palindrome.
# 	x is divisible by k.
#
#
# Return the largest integer having n digits (as a string) that is k-palindromic.
#
# Note that the integer must not have leading zeros.
#
# Example:
# Input: n = 3, k = 5
#
# Output: "595"
#
# Explanation:
#
# 595 is the largest k-palindromic integer with 3 digits.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= k <= 9
#

class Solution(object):
    def largestPalindrome(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        if n == 1:
            return str(9 - (9 % k))
        
        half_len = (n + 1) // 2
        half_palindrome = 10**half_len - 1
        
        for first_half in range(half_palindrome, 10**(half_len - 1) - 1, -1):
            if n % 2 == 0:
                pal_str = str(first_half) + str(first_half)[::-1]
            else:
                pal_str = str(first_half) + str(first_half)[-2::-1]
            
            pal_num = int(pal_str)
            if pal_num % k == 0:
                return pal_str
        
        return ""