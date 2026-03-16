# Source: https://leetcode.com/problems/strong-password-checker/   |   Difficulty: Hard
#
# Problem Description:
# A password is considered strong if the below conditions are all met:
#
#
# 	It has at least 6 characters and at most 20 characters.
# 	It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
# 	It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
#
#
# Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.
#
# In one step, you can:
#
#
# 	Insert one character to password,
# 	Delete one character from password, or
# 	Replace one character of password with another character.
#
# Example:
# Input: password = "a"
# Output: 5
#
# Constraints:
# 1 <= password.length <= 50
# 	password consists of letters, digits, dot '.' or exclamation mark '!'.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def strongPasswordChecker(self, password):
        """
        :type password: str
        :rtype: int
        """
        missing_types = 3
        if any(c.islower() for c in password):
            missing_types -= 1
        if any(c.isupper() for c in password):
            missing_types -= 1
        if any(c.isdigit() for c in password):
            missing_types -= 1

        change = 0
        one_mod = two_mod = 0
        i = 2
        while i < len(password):
            if password[i] == password[i-1] == password[i-2]:
                length = 2
                while i < len(password) and password[i] == password[i-1]:
                    length += 1
                    i += 1
                change += length // 3
                if length % 3 == 0:
                    one_mod += 1
                elif length % 3 == 1:
                    two_mod += 1
            else:
                i += 1

        if len(password) < 6:
            return max(missing_types, 6 - len(password))
        elif len(password) <= 20:
            return max(missing_types, change)
        else:
            delete = len(password) - 20
            change -= min(delete, one_mod * 1) // 1
            change -= min(max(delete - one_mod, 0), two_mod * 2) // 2
            change -= max(delete - one_mod - two_mod * 2, 0) // 3
            return delete + max(missing_types, change)