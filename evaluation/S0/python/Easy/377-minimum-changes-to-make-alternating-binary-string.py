# Source: https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.
#
# The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.
#
# Return the minimum number of operations needed to make s alternating.
#
# Example:
# Input: s = "0100"
# Output: 1
# Explanation: If you change the last character to '1', s will be "0101", which is alternating.
#
# Constraints:
# 1 <= s.length <= 104
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minOperations(self, s):
        """
        :type s: str
        :rtype: int
        """
        count1 = 0  # 以 '0' 开头的交替字符串的更改次数
        count2 = 0  # 以 '1' 开头的交替字符串的更改次数
        
        for i in range(len(s)):
            expected_char1 = '0' if i % 2 == 0 else '1'
            expected_char2 = '1' if i % 2 == 0 else '0'
            
            if s[i] != expected_char1:
                count1 += 1
            if s[i] != expected_char2:
                count2 += 1
        
        return min(count1, count2)