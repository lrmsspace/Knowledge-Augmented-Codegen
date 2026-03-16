# Source: https://leetcode.com/problems/html-entity-parser/   |   Difficulty: Medium
#
# Problem Description:
# HTML entity parser is the parser that takes HTML code as input and replace all the entities of the special characters by the characters itself.
#
# The special characters and their entities for HTML are:
#
#
# 	Quotation Mark: the entity is &quot; and symbol character is ".
# 	Single Quote Mark: the entity is &apos; and symbol character is '.
# 	Ampersand: the entity is &amp; and symbol character is &.
# 	Greater Than Sign: the entity is &gt; and symbol character is >.
# 	Less Than Sign: the entity is &lt; and symbol character is <.
# 	Slash: the entity is &frasl; and symbol character is /.
#
#
# Given the input text string to the HTML parser, you have to implement the entity parser.
#
# Return the text after replacing the entities by the special characters.
#
# Example:
# Input: text = "&amp; is an HTML entity but &ambassador; is not."
# Output: "& is an HTML entity but &ambassador; is not."
# Explanation: The parser will replace the &amp; entity by &
#
# Constraints:
# 1 <= text.length <= 105
# 	The string may contain any possible characters out of all the 256 ASCII characters.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
#   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
#   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
#   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
#   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
# - Aho-Corasick Algorithm for Pattern Searching (trie, queue, bitset, aho-corasick, bfs)
#   • When to use: Use when searching for multiple patterns simultaneously within a larger text. It is highly efficient for finding all occurrences of a dictionary of keywords.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing efficient simultaneous searching for all patterns in a text. It typically achieves O(N + M + K) time complexity, where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: All patterns in the dictionary are correctly represented as paths in the trie structure.; For any state `s`, its failure link `fail[s]` points to the longest proper prefix of the string represented by `s` that is also a suffix of `s` and exists in the trie.
#   • Tips: Build the trie first from all patterns, representing each pattern as a path.; Use BFS to construct failure links, pointing to the longest proper prefix of the current state's string that is also a suffix.
#   • Pitfalls: Incorrectly building failure links can lead to wrong matches or infinite loops.; High memory usage if the pattern set is very large or patterns are excessively long.
# - Expression parsing (stack, simulation)
#   • When to use: When evaluating or converting arithmetic or logical expressions involving various operators, including unary and binary, and handling different associativities. It's useful for implementing calculators or compilers.
#   • Idea: This technique involves using stacks to parse and evaluate expressions, correctly handling operator precedence and associativity, including unary and right-associative operators. It typically processes expressions in O(N) time, where N is the expression length.
#   • Invariants: The operator stack always maintains operators in increasing order of precedence from bottom to top (excluding parentheses).; When processing an operand, it is immediately pushed onto the operand stack.
#   • Tips: Distinguish unary from binary operators based on context (e.g., preceding token).; Assign higher precedence to unary operators than most binary ones.
#   • Pitfalls: Incorrectly identifying unary vs. binary operators based on context.; Failing to correctly implement operator precedence rules.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def entityParser(self, text):
        """
        :type text: str
        :rtype: str
        """
        entities = {
            "&quot;": '"',
            "&apos;": "'",
            "&amp;": '&',
            "&gt;": '>',
            "&lt;": '<',
            "&frasl;": '/',
        }

        for entity, char in entities.items():
            text = text.replace(entity, char)

        return text