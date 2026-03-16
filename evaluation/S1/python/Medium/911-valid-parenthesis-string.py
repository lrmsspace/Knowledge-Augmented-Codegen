# Source: https://leetcode.com/problems/valid-parenthesis-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
#
# The following rules define a valid string:
#
#
# 	Any left parenthesis '(' must have a corresponding right parenthesis ')'.
# 	Any right parenthesis ')' must have a corresponding left parenthesis '('.
# 	Left parenthesis '(' must go before the corresponding right parenthesis ')'.
# 	'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
#
# Example:
# Input: s = "()"
# Output: true
#
# Constraints:
# 1 <= s.length <= 100
# 	s[i] is '(', ')' or '*'.
#
# Helpful references (internal KB):
# - Balanced bracket sequences (number, counting)
#   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
#   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
#   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
#   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
#   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
#   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
#   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
#   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
#   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def checkValidString(self, s):
        """
        :type s: str
        :rtype: bool
        """
        low = 0  # Minimum number of open parentheses
        high = 0 # Maximum number of open parentheses

        for char in s:
            if char == '(':
                low += 1
                high += 1
            elif char == ')':
                low = max(low - 1, 0)
                high -= 1
            else:  # char == '*'
                low = max(low - 1, 0)
                high += 1

            if high < 0:
                return False

        return low == 0