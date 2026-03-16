# Source: https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s containing only digits, return the lexicographically smallest string that can be obtained after swapping adjacent digits in s with the same parity at most once.
#
# Digits have the same parity if both are odd or both are even. For example, 5 and 9, as well as 2 and 4, have the same parity, while 6 and 9 do not.
#
# Example:
# Input: s = "45320"
#
# Output: "43520"
#
# Explanation: 
#
# s[1] == '5' and s[2] == '3' both have the same parity, and swapping them results in the lexicographically smallest string.
#
# Constraints:
# 2 <= s.length <= 100
# 	s consists only of digits.
#

class Solution(object):
    def getSmallestString(self, s):
        """
        :type s: str
        :rtype: str
        """
        even_digits = sorted([ch for ch in s if int(ch) % 2 == 0])
        odd_digits = sorted([ch for ch in s if int(ch) % 2 != 0])
        
        even_index, odd_index = 0, 0
        result = []
        
        for ch in s:
            if int(ch) % 2 == 0:
                result.append(even_digits[even_index])
                even_index += 1
            else:
                result.append(odd_digits[odd_index])
                odd_index += 1
        
        return ''.join(result)