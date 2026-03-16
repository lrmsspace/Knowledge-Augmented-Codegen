# Source: https://leetcode.com/problems/detect-capital/   |   Difficulty: Easy
#
# Problem Description:
# We define the usage of capitals in a word to be right when one of the following cases holds:
#
#
# 	All letters in this word are capitals, like "USA".
# 	All letters in this word are not capitals, like "leetcode".
# 	Only the first letter in this word is capital, like "Google".
#
#
# Given a string word, return true if the usage of capitals in it is right.
#
# Example:
# Input: word = "USA"
# Output: true
#
# Constraints:
# 1 <= word.length <= 100
# 	word consists of lowercase and uppercase English letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
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
    def detectCapitalUse(self, word):
        """
        :type word: str
        :rtype: bool
        """
        return word.isupper() or word.islower() or (word[0].isupper() and word[1:].islower())