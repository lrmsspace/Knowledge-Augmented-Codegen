# Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s (0-indexed)​​​​​​. You are asked to perform the following operation on s​​​​​​ until you get a sorted string:
#
#
# 	Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
# 	Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
# 	Swap the two characters at indices i - 1​​​​ and j​​​​​.
# 	Reverse the suffix starting at index i​​​​​​.
#
#
# Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
#
# Example:
# Input: s = "cba"
# Output: 5
# Explanation: The simulation goes as follows:
# Operation 1: i=2, j=2. Swap s[1] and s[2] to get s="cab", then reverse the suffix starting at 2. Now, s="cab".
# Operation 2: i=1, j=2. Swap s[0] and s[2] to get s="bac", then reverse the suffix starting at 1. Now, s="bca".
# Operation 3: i=2, j=2. Swap s[1] and s[2] to get s="bac", then reverse the suffix starting at 2. Now, s="bac".
# Operation 4: i=1, j=1. Swap s[0] and s[1] to get s="abc", then reverse the suffix starting at 1. Now, s="acb".
# Operation 5: i=2, j=2. Swap s[1] and s[2] to get s="abc", then reverse the suffix starting at 2. Now, s="abc".
#
# Constraints:
# 1 <= s.length <= 3000
# 	s​​​​​​ consists only of lowercase English letters.
#

class Solution(object):
    def makeStringSorted(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        fact = [1] * (n + 1)
        for i in range(1, n + 1):
            fact[i] = fact[i - 1] * i % MOD

        count = [0] * 26
        for ch in s:
            count[ord(ch) - ord('a')] += 1

        def mod_inv(x):
            return pow(x, MOD - 2, MOD)

        res = 0
        for i in range(n):
            for ch in range(ord(s[i]) - ord('a')):
                if count[ch] == 0:
                    continue
                count[ch] -= 1
                denom = 1
                for c in count:
                    denom = denom * fact[c] % MOD
                res = (res + fact[n - i - 1] * mod_inv(denom)) % MOD
                count[ch] += 1
            count[ord(s[i]) - ord('a')] -= 1

        return res