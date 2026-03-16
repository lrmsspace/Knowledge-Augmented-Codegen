# Source: https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer k.
#
# Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
#
#
# 	The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are placed in a cyclic order, for all i in the range [0, n - 1].
#
#
# For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.
#
# You can change any letter of s to any other lowercase English letter, any number of times.
#
# Return a string denoting the lexicographically smallest string t you can get after some changes, such that distance(s, t) <= k.
#
# Example:
# Input: s = "zbbz", k = 3
#
# Output: "aaaz"
#
# Explanation:
#
# Change s to "aaaz". The distance between "zbbz" and "aaaz" is equal to k = 3.
#
# Constraints:
# 1 <= s.length <= 100
# 	0 <= k <= 2000
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def getSmallestString(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        res = []
        n = len(s)
        
        for i in range(n):
            if k <= 0:
                res.append(s[i])
                continue
            
            diff_a = (ord(s[i]) - ord('a')) % 26
            diff_z = (ord('z') - ord(s[i])) % 26
            
            if diff_a >= diff_z:
                if diff_a <= k:
                    res.append('a')
                    k -= diff_a
                else:
                    new_char = chr(ord(s[i]) - k)
                    res.append(new_char)
                    k = 0
            else:
                if diff_z <= k:
                    res.append('z')
                    k -= diff_z
                else:
                    new_char = chr(ord(s[i]) + k)
                    res.append(new_char)
                    k = 0
        
        return ''.join(res)