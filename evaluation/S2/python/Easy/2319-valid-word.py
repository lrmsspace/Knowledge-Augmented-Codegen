# Source: https://leetcode.com/problems/valid-word/   |   Difficulty: Easy
#
# Problem Description:
# A word is considered valid if:
#
#
# 	It contains a minimum of 3 characters.
# 	It contains only digits (0-9), and English letters (uppercase and lowercase).
# 	It includes at least one vowel.
# 	It includes at least one consonant.
#
#
# You are given a string word.
#
# Return true if word is valid, otherwise, return false.
#
# Notes:
#
#
# 	'a', 'e', 'i', 'o', 'u', and their uppercases are vowels.
# 	A consonant is an English letter that is not a vowel.
#
# Example:
# Input: word = "234Adas"
#
# Output: true
#
# Explanation:
#
# This word satisfies the conditions.
#
# Constraints:
# 1 <= word.length <= 20
# 	word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Ternary Search (interval, number, binary-search, greedy)
#   • When to use: Use when searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It efficiently narrows down the search space by evaluating the function at two internal points.
#   • Idea: Ternary search is a divide and conquer algorithm that finds the extremum of a unimodal function within an interval by repeatedly reducing the search space by approximately one-third. It has a logarithmic time complexity, similar to binary search, but requires two function evaluations per step.
#   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with the function value at m2.
#   • Tips: Handle discrete intervals by checking remaining points when interval size is small.; Consider Golden Section Search to reduce function evaluations per iteration.
#   • Pitfalls: Incorrectly applying to non-unimodal functions.; Infinite loops if stopping condition for discrete intervals is not handled.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isValid(self, word):
        """
        :type word: str
        :rtype: bool
        """
        if len(word) < 3:
            return False

        vowels = set("aeiouAEIOU")
        has_vowel = False
        has_consonant = False

        for char in word:
            if char.isalnum():  # Check if it's a digit or letter
                if char in vowels:
                    has_vowel = True
                else:
                    has_consonant = True
            else:
                return False  # Contains invalid character

        return has_vowel and has_consonant