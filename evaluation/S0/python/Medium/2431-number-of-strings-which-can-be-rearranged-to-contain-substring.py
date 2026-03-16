# Source: https://leetcode.com/problems/number-of-strings-which-can-be-rearranged-to-contain-substring/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n.
#
# A string s is called good if it contains only lowercase English characters and it is possible to rearrange the characters of s such that the new string contains "leet" as a substring.
#
# For example:
#
#
# 	The string "lteer" is good because we can rearrange it to form "leetr" .
# 	"letl" is not good because we cannot rearrange it to contain "leet" as a substring.
#
#
# Return the total number of good strings of length n.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: n = 4
# Output: 12
# Explanation: The 12 strings which can be rearranged to have "leet" as a substring are: "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
#
# Constraints:
# 1 <= n <= 105
#

class Solution(object):
    def stringCount(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        if n < 4:
            return 0
        
        # Calculate 26^(n-4) % MOD
        pow_26 = pow(26, n - 4, MOD)
        
        # Calculate the number of ways to arrange 'leet' in the string
        arrangements = 12  # 'leet' can be arranged in 12 different ways
        
        # Total good strings
        total_good_strings = (arrangements * pow_26) % MOD
        
        return total_good_strings