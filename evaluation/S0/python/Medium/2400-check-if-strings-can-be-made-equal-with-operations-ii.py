# Source: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.
#
# You can apply the following operation on any of the two strings any number of times:
#
#
# 	Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at those indices in the string.
#
#
# Return true if you can make the strings s1 and s2 equal, and false otherwise.
#
# Example:
# Input: s1 = "abcdba", s2 = "cabdab"
# Output: true
# Explanation: We can apply the following operations on s1:
# - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
# - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
# - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.
#
# Constraints:
# n == s1.length == s2.length
# 	1 <= n <= 105
# 	s1 and s2 consist only of lowercase English letters.
#

class Solution(object):
    def checkStrings(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        from collections import Counter

        even_s1 = Counter(s1[i] for i in range(0, len(s1), 2))
        odd_s1 = Counter(s1[i] for i in range(1, len(s1), 2))
        even_s2 = Counter(s2[i] for i in range(0, len(s2), 2))
        odd_s2 = Counter(s2[i] for i in range(1, len(s2), 2))

        return even_s1 == even_s2 and odd_s1 == odd_s2