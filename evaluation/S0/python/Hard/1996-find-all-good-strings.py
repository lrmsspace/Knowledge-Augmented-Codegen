# Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
#
# Problem Description:
# Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
#
# A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
#
# Example:
# Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
# Output: 51 
# Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
#
# Constraints:
# s1.length == n
# 	s2.length == n
# 	s1 <= s2
# 	1 <= n <= 500
# 	1 <= evil.length <= 50
# 	All strings consist of lowercase English letters.
#

class Solution(object):
    def findGoodStrings(self, n, s1, s2, evil):
        """
        :type n: int
        :type s1: str
        :type s2: str
        :type evil: str
        :rtype: int
        """
        MOD = 10**9 + 7
        m = len(evil)

        # KMP preprocessing
        lps = [0] * m
        j = 0
        for i in range(1, m):
            while j > 0 and evil[i] != evil[j]:
                j = lps[j - 1]
            if evil[i] == evil[j]:
                j += 1
                lps[i] = j

        @lru_cache(None)
        def dp(pos, evil_matched, is_prefix_s1, is_prefix_s2):
            if evil_matched == m:
                return 0
            if pos == n:
                return 1

            low = s1[pos] if is_prefix_s1 else 'a'
            high = s2[pos] if is_prefix_s2 else 'z'
            total = 0

            for c in range(ord(low), ord(high) + 1):
                ch = chr(c)
                new_evil_matched = evil_matched
                while new_evil_matched > 0 and ch != evil[new_evil_matched]:
                    new_evil_matched = lps[new_evil_matched - 1]
                if ch == evil[new_evil_matched]:
                    new_evil_matched += 1

                total += dp(
                    pos + 1,
                    new_evil_matched,
                    is_prefix_s1 and (ch == low),
                    is_prefix_s2 and (ch == high)
                )
                total %= MOD

            return total

        return dp(0, 0, True, True)