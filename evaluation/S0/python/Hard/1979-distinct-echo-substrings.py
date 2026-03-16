# Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
#
# Problem Description:
# Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
#
# Example:
# Input: text = "abcabcabc"
# Output: 3
# Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
#
# Constraints:
# 1 <= text.length <= 2000
# 	text has only lowercase English letters.
#

class Solution(object):
    def distinctEchoSubstrings(self, text):
        """
        :type text: str
        :rtype: int
        """
        n = len(text)
        mod = 10**9 + 7
        base = 31

        # Precompute powers of base
        power = [1] * (n + 1)
        for i in range(1, n + 1):
            power[i] = (power[i - 1] * base) % mod

        # Precompute prefix hashes
        prefix_hash = [0] * (n + 1)
        for i in range(n):
            prefix_hash[i + 1] = (prefix_hash[i] * base + ord(text[i]) - ord('a') + 1) % mod

        def get_hash(l, r):
            """Get hash of substring text[l:r]"""
            return (prefix_hash[r] - (prefix_hash[l] * power[r - l]) % mod + mod) % mod

        seen = set()
        for length in range(1, n // 2 + 1):
            for start in range(n - 2 * length + 1):
                if get_hash(start, start + length) == get_hash(start + length, start + 2 * length):
                    seen.add(get_hash(start, start + 2 * length))

        return len(seen)