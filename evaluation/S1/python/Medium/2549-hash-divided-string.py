# Source: https://leetcode.com/problems/hash-divided-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s of length n and an integer k, where n is a multiple of k. Your task is to hash the string s into a new string called result, which has a length of n / k.
#
# First, divide s into n / k substrings, each with a length of k. Then, initialize result as an empty string.
#
# For each substring in order from the beginning:
#
#
# 	The hash value of a character is the index of that character in the English alphabet (e.g., 'a' → 0, 'b' → 1, ..., 'z' → 25).
# 	Calculate the sum of all the hash values of the characters in the substring.
# 	Find the remainder of this sum when divided by 26, which is called hashedChar.
# 	Identify the character in the English lowercase alphabet that corresponds to hashedChar.
# 	Append that character to the end of result.
#
#
# Return result.
#
# Example:
# Input: s = "abcd", k = 2
#
# Output: "bf"
#
# Explanation:
#
# First substring: "ab", 0 + 1 = 1, 1 % 26 = 1, result[0] = 'b'.
#
# Second substring: "cd", 2 + 3 = 5, 5 % 26 = 5, result[1] = 'f'.
#
# Constraints:
# 1 <= k <= 100
# 	k <= s.length <= 1000
# 	s.length is divisible by k.
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def stringHash(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        result = []
        n = len(s)
        
        for i in range(0, n, k):
            substring = s[i:i+k]
            hash_sum = sum(ord(char) - ord('a') for char in substring)
            hashed_char_index = hash_sum % 26
            hashed_char = chr(hashed_char_index + ord('a'))
            result.append(hashed_char)
        
        return ''.join(result)