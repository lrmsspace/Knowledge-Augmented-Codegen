# Source: https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a binary string s consisting only of zeroes and ones.
#
# A substring of s is considered balanced if all zeroes are before ones and the number of zeroes is equal to the number of ones inside the substring. Notice that the empty substring is considered a balanced substring.
#
# Return the length of the longest balanced substring of s.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "01000111"
# Output: 6
# Explanation: The longest balanced substring is "000111", which has length 6.
#
# Constraints:
# 1 <= s.length <= 50
# 	'0' <= s[i] <= '1'
#

class Solution(object):
    def findTheLongestBalancedSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_length = 0
        n = len(s)
        
        i = 0
        while i < n:
            if s[i] == '0':
                count_0 = 0
                count_1 = 0
                
                while i < n and s[i] == '0':
                    count_0 += 1
                    i += 1
                
                while i < n and s[i] == '1':
                    count_1 += 1
                    i += 1
                
                balanced_length = 2 * min(count_0, count_1)
                max_length = max(max_length, balanced_length)
            else:
                i += 1
        
        return max_length