# Source: https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
#
# if no such substring exists, return 0.
#
# Example:
# Input: s = "aaabb", k = 3
# Output: 3
# Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of only lowercase English letters.
# 	1 <= k <= 105
#

class Solution(object):
    def longestSubstring(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def helper(start, end):
            if end - start < k:
                return 0
            
            count = {}
            for i in range(start, end):
                count[s[i]] = count.get(s[i], 0) + 1
            
            for mid in range(start, end):
                if count[s[mid]] < k:
                    mid_next = mid + 1
                    while mid_next < end and count[s[mid_next]] < k:
                        mid_next += 1
                    return max(helper(start, mid), helper(mid_next, end))
            
            return end - start
        
        return helper(0, len(s))