# Source: https://leetcode.com/problems/find-substring-with-given-hash-value/   |   Difficulty: Hard
#
# Problem Description:
# The hash of a 0-indexed string s of length k, given integers p and m, is computed using the following function:
#
#
# 	hash(s, p, m) = (val(s[0]) * p0 + val(s[1]) * p1 + ... + val(s[k-1]) * pk-1) mod m.
#
#
# Where val(s[i]) represents the index of s[i] in the alphabet from val('a') = 1 to val('z') = 26.
#
# You are given a string s and the integers power, modulo, k, and hashValue. Return sub, the first substring of s of length k such that hash(sub, power, modulo) == hashValue.
#
# The test cases will be generated such that an answer always exists.
#
# A substring is a contiguous non-empty sequence of characters within a string.
#
# Example:
# Input: s = "leetcode", power = 7, modulo = 20, k = 2, hashValue = 0
# Output: "ee"
# Explanation: The hash of "ee" can be computed to be hash("ee", 7, 20) = (5 * 1 + 5 * 7) mod 20 = 40 mod 20 = 0. 
# "ee" is the first substring of length 2 with hashValue 0. Hence, we return "ee".
#
# Constraints:
# 1 <= k <= s.length <= 2 * 104
# 	1 <= power, modulo <= 109
# 	0 <= hashValue < modulo
# 	s consists of lowercase English letters only.
# 	The test cases are generated such that an answer always exists.
#

class Solution(object):
    def subStrHash(self, s, power, modulo, k, hashValue):
        """
        :type s: str
        :type power: int
        :type modulo: int
        :type k: int
        :type hashValue: int
        :rtype: str
        """
        n = len(s)
        current_hash = 0
        power_k = pow(power, k - 1, modulo)
        result_index = 0

        for i in range(n - 1, -1, -1):
            current_hash = (current_hash * power + (ord(s[i]) - ord('a') + 1)) % modulo

            if i + k < n:
                current_hash = (current_hash - (ord(s[i + k]) - ord('a') + 1) * power_k) % modulo
                if current_hash < 0:
                    current_hash += modulo

            if i <= n - k and current_hash == hashValue:
                result_index = i

        return s[result_index:result_index + k]