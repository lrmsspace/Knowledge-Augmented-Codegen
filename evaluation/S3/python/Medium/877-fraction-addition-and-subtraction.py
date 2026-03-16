# Source: https://leetcode.com/problems/fraction-addition-and-subtraction/   |   Difficulty: Medium
#
# Problem Description:
# Given a string expression representing an expression of fraction addition and subtraction, return the calculation result in string format.
#
# The final result should be an irreducible fraction. If your final result is an integer, change it to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to 2/1.
#
# Example:
# Input: expression = "-1/2+1/2"
# Output: "0/1"
#
# Constraints:
# The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
# 	Each fraction (input and output) has the format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
# 	The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1, 10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
# 	The number of given fractions will be in the range [1, 10].
# 	The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
#
# Helpful references (internal KB):
# - Expression parsing (stack, simulation)
#   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
#   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
#   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
#   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
#   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
# - Expression parsing (stack, simulation)
#   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
#   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
#   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
#   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
#   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
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
    def fractionAddition(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        from math import gcd
        import re

        # Step 1: Parse the expression into a list of fractions
        fractions = re.findall(r'[+-]?\d+/\d+', expression)

        # Step 2: Initialize numerator and denominator for the result
        numerator = 0
        denominator = 1

        # Step 3: Process each fraction
        for frac in fractions:
            num, denom = map(int, frac.split('/'))
            # Update the result using the formula: a/b + c/d = (ad + bc) / bd
            numerator = numerator * denom + num * denominator
            denominator *= denom

            # Step 4: Reduce the fraction by their GCD
            common = gcd(abs(numerator), denominator)
            numerator //= common
            denominator //= common

        # Step 5: Handle the case when the numerator is zero
        if numerator == 0:
            return "0/1"

        return f"{numerator}/{denominator}"