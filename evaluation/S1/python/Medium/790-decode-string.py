# Source: https://leetcode.com/problems/decode-string/   |   Difficulty: Medium
#
# Problem Description:
# Given an encoded string, return its decoded string.
#
# The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
#
# You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
#
# The test cases are generated so that the length of the output will never exceed 105.
#
# Example:
# Input: s = "3[a]2[bc]"
# Output: "aaabcbc"
#
# Constraints:
# 1 <= s.length <= 30
# 	s consists of lowercase English letters, digits, and square brackets '[]'.
# 	s is guaranteed to be a valid input.
# 	All the integers in s are in the range [1, 300].
#
# Helpful references (internal KB):
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
#   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
#   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
#   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
#   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
# - Balanced bracket sequences (number, counting)
#   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
#   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
#   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
#   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
#   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def decodeString(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        current_num = 0
        current_str = ''
        
        for char in s:
            if char.isdigit():
                current_num = current_num * 10 + int(char)
            elif char == '[':
                stack.append((current_str, current_num))
                current_str = ''
                current_num = 0
            elif char == ']':
                last_str, num = stack.pop()
                current_str = last_str + num * current_str
            else:
                current_str += char
        
        return current_str