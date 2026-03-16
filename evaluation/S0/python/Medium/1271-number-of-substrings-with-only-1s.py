# Source: https://leetcode.com/problems/number-of-substrings-with-only-1s/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: s = "0110111"
# Output: 9
# Explanation: There are 9 substring in total with only 1's characters.
# "1" -> 5 times.
# "11" -> 3 times.
# "111" -> 1 time.
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def numSub(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        count = 0
        result = 0
        
        for char in s:
            if char == '1':
                count += 1
            else:
                result += count * (count + 1) // 2
                count = 0
        
        result += count * (count + 1) // 2
        return result % MOD