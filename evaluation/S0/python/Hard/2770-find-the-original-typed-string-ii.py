# Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
#
# Problem Description:
# Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
#
# You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
#
# Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: word = "aabbccdd", k = 7
#
# Output: 5
#
# Explanation:
#
# The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
#
# Constraints:
# 1 <= word.length <= 5 * 105
#  word consists only of lowercase English letters.
#  1 <= k <= 2000
#

class Solution(object):
    def possibleStringCount(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(word)
        
        # Precompute factorials and inverse factorials for combinations
        max_len = n + 1
        fact = [1] * max_len
        inv_fact = [1] * max_len
        
        for i in range(2, max_len):
            fact[i] = fact[i-1] * i % MOD
        
        inv_fact[max_len - 1] = pow(fact[max_len - 1], MOD - 2, MOD)
        for i in range(max_len - 2, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
        
        def comb(a, b):
            if a < b or b < 0:
                return 0
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD
        
        total_count = 1
        i = 0
        
        while i < n:
            j = i
            while j < n and word[j] == word[i]:
                j += 1
            
            length = j - i
            count_for_char = 0
            
            for remove_count in range(length):
                new_length = length - remove_count
                if new_length >= k:
                    count_for_char = (count_for_char + comb(length - 1, new_length - 1)) % MOD
            
            total_count = (total_count * count_for_char) % MOD
            i = j
        
        return total_count