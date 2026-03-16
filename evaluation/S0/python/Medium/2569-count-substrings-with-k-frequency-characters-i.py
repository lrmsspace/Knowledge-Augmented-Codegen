# Source: https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s and an integer k, return the total number of substrings of s where at least one character appears at least k times.
#
# Example:
# Input: s = "abacb", k = 2
#
# Output: 4
#
# Explanation:
#
# The valid substrings are:
#
#
# 	"aba" (character 'a' appears 2 times).
# 	"abac" (character 'a' appears 2 times).
# 	"abacb" (character 'a' appears 2 times).
# 	"bacb" (character 'b' appears 2 times).
#
# Constraints:
# 1 <= s.length <= 3000
# 	1 <= k <= s.length
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def numberOfSubstrings(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        count = 0
        
        for i in range(n):
            freq = {}
            for j in range(i, n):
                freq[s[j]] = freq.get(s[j], 0) + 1
                if freq[s[j]] >= k:
                    count += (n - j)
                    break
                    
        return count