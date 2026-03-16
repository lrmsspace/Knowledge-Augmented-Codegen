# Source: https://leetcode.com/problems/minimize-result-by-adding-parentheses-to-expression/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string expression of the form "<num1>+<num2>" where <num1> and <num2> represent positive integers.
#
# Add a pair of parentheses to expression such that after the addition of parentheses, expression is a valid mathematical expression and evaluates to the smallest possible value. The left parenthesis must be added to the left of '+' and the right parenthesis must be added to the right of '+'.
#
# Return expression after adding a pair of parentheses such that expression evaluates to the smallest possible value. If there are multiple answers that yield the same result, return any of them.
#
# The input has been generated such that the original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
#
# Example:
# Input: expression = "247+38"
# Output: "2(47+38)"
# Explanation: The expression evaluates to 2 * (47 + 38) = 2 * 85 = 170.
# Note that "2(4)7+38" is invalid because the right parenthesis must be to the right of the '+'.
# It can be shown that 170 is the smallest possible value.
#
# Constraints:
# 3 <= expression.length <= 10
# 	expression consists of digits from '1' to '9' and '+'.
# 	expression starts and ends with digits.
# 	expression contains exactly one '+'.
# 	The original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
#
# Helpful references (internal KB):
# - Expression parsing (stack, simulation)
#   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
#   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
#   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
#   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
#   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
# - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
#   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
#   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
#   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
#   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
#   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimizeResult(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        plus_index = expression.index('+')
        num1 = expression[:plus_index]
        num2 = expression[plus_index + 1:]
        
        min_value = float('inf')
        result = ""
        
        for i in range(len(num1)):
            for j in range(len(num2)):
                left_multiplier = int(num1[:i]) if i > 0 else 1
                right_multiplier = int(num2[j + 1:]) if j + 1 < len(num2) else 1
                middle_sum = int(num1[i:]) + int(num2[:j + 1])
                
                current_value = left_multiplier * middle_sum * right_multiplier
                
                if current_value < min_value:
                    min_value = current_value
                    result = f"{num1[:i]}({num1[i:]}+{num2[:j + 1]}){num2[j + 1:]}"
        
        return result