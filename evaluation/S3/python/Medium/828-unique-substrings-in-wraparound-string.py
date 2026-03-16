# Source: https://leetcode.com/problems/unique-substrings-in-wraparound-string/   |   Difficulty: Medium
#
# Problem Description:
# We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
#
#
# 	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
#
#
# Given a string s, return the number of unique non-empty substrings of s are present in base.
#
# Example:
# Input: s = "a"
# Output: 1
# Explanation: Only the substring "a" of s is in base.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Suffix Automaton (string, enumeration)
#   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
#   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
#   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
#   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
#   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
#   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
#   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
#   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
#   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
#   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findSubstringInWraproundString(self, s):
        """
        :type s: str
        :rtype: int
        """
        if not s:
            return 0

        max_len = [0] * 26
        current_len = 0

        for i in range(len(s)):
            if i > 0 and (ord(s[i]) - ord(s[i - 1])) % 26 == 1:
                current_len += 1
            else:
                current_len = 1

            index = ord(s[i]) - ord('a')
            max_len[index] = max(max_len[index], current_len)

        return sum(max_len)