# Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
#
#
# 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
# 	A substring that contains a certain character c must also contain all occurrences of c.
#
#
# Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
#
# Notice that you can return the substrings in any order.
#
# Example:
# Input: s = "adefaddaccc"
# Output: ["e","f","ccc"]
# Explanation: The following are all the possible substrings that meet the conditions:
# [
#   "adefaddaccc"
#   "adefadda",
#   "ef",
#   "e",
#   "f",
#   "ccc",
# ]
# If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
#
# Constraints:
# 1 <= s.length <= 105
# 	s contains only lowercase English letters.
#

class Solution(object):
    def maxNumOfSubstrings(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        n = len(s)
        intervals = []
        for c in set(s):
            left = s.index(c)
            right = s.rindex(c)
            i = left
            while i <= right:
                left = min(left, s.index(s[i]))
                right = max(right, s.rindex(s[i]))
                i += 1
            if left == s.index(c):
                intervals.append((left, right))
        intervals.sort(key=lambda x: x[1])
        res = []
        end = -1
        for l, r in intervals:
            if l > end:
                res.append(s[l:r+1])
                end = r
        return res