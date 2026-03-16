# Source: https://leetcode.com/problems/number-of-atoms/   |   Difficulty: Hard
#
# Problem Description:
# Given a string formula representing a chemical formula, return the count of each atom.
#
# The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
#
# One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.
#
#
# 	For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
#
#
# Two formulas are concatenated together to produce another formula.
#
#
# 	For example, "H2O2He3Mg4" is also a formula.
#
#
# A formula placed in parentheses, and a count (optionally added) is also a formula.
#
#
# 	For example, "(H2O2)" and "(H2O2)3" are formulas.
#
#
# Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
#
# The test cases are generated so that all the values in the output fit in a 32-bit integer.
#
# Example:
# Input: formula = "H2O"
# Output: "H2O"
# Explanation: The count of elements are {'H': 2, 'O': 1}.
#
# Constraints:
# 1 <= formula.length <= 1000
# 	formula consists of English letters, digits, '(', and ')'.
# 	formula is always valid.
#
# Helpful references (internal KB):
# - String Sorts (array, string, number, radix-sort, counting-sort)
#   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
#   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
#   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
#   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
#   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
# - Balanced bracket sequences (number, counting)
#   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
#   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
#   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
#   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
#   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
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
    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        import re
        from collections import defaultdict

        def parse():
            stack = [defaultdict(int)]
            i, n = 0, len(formula)

            while i < n:
                if formula[i] == '(':
                    stack.append(defaultdict(int))
                    i += 1
                elif formula[i] == ')':
                    top = stack.pop()
                    i += 1
                    num = 0
                    while i < n and formula[i].isdigit():
                        num = num * 10 + int(formula[i])
                        i += 1
                    num = max(num, 1)
                    for atom, count in top.items():
                        stack[-1][atom] += count * num
                else:
                    j = i + 1
                    while j < n and formula[j].islower():
                        j += 1
                    atom = formula[i:j]
                    i = j
                    num = 0
                    while i < n and formula[i].isdigit():
                        num = num * 10 + int(formula[i])
                        i += 1
                    num = max(num, 1)
                    stack[-1][atom] += num

            return stack.pop()

        atom_counts = parse()
        return ''.join(atom + (str(count) if count > 1 else '') for atom, count in sorted(atom_counts.items()))