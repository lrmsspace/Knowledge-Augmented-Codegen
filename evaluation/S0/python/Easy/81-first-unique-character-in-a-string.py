# Source: https://leetcode.com/problems/first-unique-character-in-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.
#
# Example:
# Input: s = "leetcode"
#
# Output: 0
#
# Explanation:
#
# The character 'l' at index 0 is the first character that does not occur at any other index.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def firstUniqChar(self, s):
        """
        :type s: str
        :rtype: int
        """
        char_count = {}
        
        # 统计每个字符出现的次数
        for char in s:
            if char in char_count:
                char_count[char] += 1
            else:
                char_count[char] = 1
        
        # 查找第一个只出现一次的字符
        for index, char in enumerate(s):
            if char_count[char] == 1:
                return index
        
        return -1