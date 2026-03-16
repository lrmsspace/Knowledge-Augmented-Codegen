# Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
#
# The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
#
# Any two characters may be swapped, even if they are not adjacent.
#
# Example:
# Input: s = "111000"
# Output: 1
# Explanation: Swap positions 1 and 4: "111000" -> "101010"
# The string is now alternating.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minSwaps(self, s):
        """
        :type s: str
        :rtype: int
        """
        count0 = s.count('0')
        count1 = s.count('1')
        
        if abs(count0 - count1) > 1:
            return -1
        
        def calculate_swaps(start_char):
            swaps = 0
            for i in range(len(s)):
                expected_char = start_char if i % 2 == 0 else ('1' if start_char == '0' else '0')
                if s[i] != expected_char:
                    swaps += 1
            return swaps // 2
        
        if count0 > count1:
            return calculate_swaps('0')
        elif count1 > count0:
            return calculate_swaps('1')
        else:
            return min(calculate_swaps('0'), calculate_swaps('1'))