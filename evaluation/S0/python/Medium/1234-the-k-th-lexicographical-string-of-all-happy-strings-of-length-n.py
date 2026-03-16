# Source: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/   |   Difficulty: Medium
#
# Problem Description:
# A happy string is a string that:
#
#
# 	consists only of letters of the set ['a', 'b', 'c'].
# 	s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
#
#
# For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
#
# Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
#
# Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
#
# Example:
# Input: n = 1, k = 3
# Output: "c"
# Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
#
# Constraints:
# 1 <= n <= 10
# 	1 <= k <= 100
#

class Solution(object):
    def getHappyString(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        def backtrack(current):
            if len(current) == n:
                result.append("".join(current))
                return
            for char in ['a', 'b', 'c']:
                if not current or current[-1] != char:
                    current.append(char)
                    backtrack(current)
                    current.pop()

        result = []
        backtrack([])
        if k <= len(result):
            return result[k - 1]
        else:
            return ""