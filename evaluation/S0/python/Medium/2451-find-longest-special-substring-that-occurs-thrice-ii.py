# Source: https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s that consists of lowercase English letters.
#
# A string is called special if it is made up of only a single character. For example, the string "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.
#
# Return the length of the longest special substring of s which occurs at least thrice, or -1 if no special substring occurs at least thrice.
#
# A substring is a contiguous non-empty sequence of characters within a string.
#
# Example:
# Input: s = "aaaa"
# Output: 2
# Explanation: The longest special substring which occurs thrice is "aa": substrings "aaaa", "aaaa", and "aaaa".
# It can be shown that the maximum length achievable is 2.
#
# Constraints:
# 3 <= s.length <= 5 * 105
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def maximumLength(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_len = -1
        count = {}
        
        n = len(s)
        i = 0
        
        while i < n:
            char = s[i]
            length = 1
            
            while i + 1 < n and s[i + 1] == char:
                length += 1
                i += 1
            
            if char not in count:
                count[char] = []
            count[char].append(length)
            
            i += 1
        
        for lengths in count.values():
            lengths.sort(reverse=True)
            if len(lengths) >= 3:
                max_len = max(max_len, lengths[2])
        
        return max_len