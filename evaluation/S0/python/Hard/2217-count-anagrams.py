# Source: https://leetcode.com/problems/count-anagrams/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.
#
# A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.
#
#
# 	For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
#
#
# Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "too hot"
# Output: 18
# Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters and spaces ' '.
# 	There is single space between consecutive words.
#

class Solution(object):
    def countAnagrams(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        MAX = 10**5
        
        # Precompute factorials and inverse factorials
        fact = [1] * (MAX + 1)
        for i in range(2, MAX + 1):
            fact[i] = fact[i - 1] * i % MOD
        
        inv_fact = [1] * (MAX + 1)
        inv_fact[MAX] = pow(fact[MAX], MOD - 2, MOD)
        for i in range(MAX - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
        
        def nCr(n, r):
            if r > n or r < 0:
                return 0
            return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD
        
        result = 1
        words = s.split()
        
        for word in words:
            count = {}
            for char in word:
                count[char] = count.get(char, 0) + 1
            
            length = len(word)
            for freq in count.values():
                result = result * nCr(length, freq) % MOD
                length -= freq
        
        return result