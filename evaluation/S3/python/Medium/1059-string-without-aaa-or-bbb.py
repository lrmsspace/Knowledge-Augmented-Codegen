# Source: https://leetcode.com/problems/string-without-aaa-or-bbb/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers a and b, return any string s such that:
#
#
# 	s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
# 	The substring 'aaa' does not occur in s, and
# 	The substring 'bbb' does not occur in s.
#
# Example:
# Input: a = 1, b = 2
# Output: "abb"
# Explanation: "abb", "bab" and "bba" are all correct answers.
#
# Constraints:
# 0 <= a, b <= 100
# 	It is guaranteed such an s exists for the given a and b.
#
# Helpful references (internal KB):
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
#   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
#   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
#   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
#   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
#   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def strWithout3a3b(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: str
        """
        result = []
        while a > 0 or b > 0:
            if (len(result) >= 2 and result[-1] == result[-2]):
                if result[-1] == 'a':
                    result.append('b')
                    b -= 1
                else:
                    result.append('a')
                    a -= 1
            else:
                if a >= b:
                    result.append('a')
                    a -= 1
                else:
                    result.append('b')
                    b -= 1
        return ''.join(result)