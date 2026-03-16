# Source: https://leetcode.com/problems/find-the-string-with-lcp/   |   Difficulty: Hard
#
# Problem Description:
# We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:
#
#
# 	lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
#
#
# Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.
#
# A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.
#
# Example:
# Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
# Output: "abab"
# Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".
#
# Constraints:
# 1 <= n == lcp.length == lcp[i].length <= 1000
# 	0 <= lcp[i][j] <= n
#

class Solution(object):
    def findTheString(self, lcp):
        """
        :type lcp: List[List[int]]
        :rtype: str
        """
        n = len(lcp)
        word = [''] * n
        next_char = 'a'

        for i in range(n):
            if word[i] == '':
                if next_char > 'z':
                    return ""
                word[i] = next_char
                next_char = chr(ord(next_char) + 1)

            for j in range(i, n):
                if lcp[i][j] > 0:
                    if word[j] == '':
                        word[j] = word[i]
                    elif word[j] != word[i]:
                        return ""

                    expected_lcp = lcp[i][j]
                    for k in range(expected_lcp):
                        if i + k >= n or j + k >= n or word[i + k] != word[j + k]:
                            return ""
                    if i + expected_lcp < n and j + expected_lcp < n:
                        if lcp[i + expected_lcp][j + expected_lcp] != 0:
                            return ""
        return ''.join(word)