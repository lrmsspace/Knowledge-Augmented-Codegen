# Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
#
# Problem Description:
# We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
#
#
# 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
#
#
# Given a string s, return the number of unique non-empty substrings of s are present in base.
#
# Example:
# Input: s = "a"
# Output: 1
# Explanation: Only the substring "a" of s is in base.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
#

class Solution(object):
    def findSubstringInWraproundString(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = [0] * 26  # 用于记录以每个字母结尾的最长子串长度
        max_len = 0  # 当前连续子串的长度

        for i in range(len(s)):
            if i > 0 and (ord(s[i]) - ord(s[i - 1]) - 1) % 26 == 0:
                max_len += 1
            else:
                max_len = 1

            index = ord(s[i]) - ord('a')
            count[index] = max(count[index], max_len)

        return sum(count)