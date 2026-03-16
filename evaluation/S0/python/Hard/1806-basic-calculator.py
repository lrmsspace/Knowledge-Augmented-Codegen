# Source: https://leetcode.com/problems/basic-calculator/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
#
# Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
#
# Example:
# Input: s = "1 + 1"
# Output: 2
#
# Constraints:
# 1 <= s.length <= 3 * 105
# 	s consists of digits, '+', '-', '(', ')', and ' '.
# 	s represents a valid expression.
# 	'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
# 	'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
# 	There will be no two consecutive operators in the input.
# 	Every number and running calculation will fit in a signed 32-bit integer.
#

class Solution(object):
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        operand = 0
        result = 0  # For the on-going result
        sign = 1    # 1 means positive, -1 means negative

        for ch in s:
            if ch.isdigit():
                # Forming operand, since it could be more than one digit
                operand = (operand * 10) + int(ch)

            elif ch == '+':
                # Evaluate the expression to the left,
                # with result, sign, operand
                result += sign * operand
                sign = 1
                operand = 0

            elif ch == '-':
                result += sign * operand
                sign = -1
                operand = 0

            elif ch == '(':
                # Push the result and sign on to the stack, for later
                # We push the result first, then sign
                stack.append(result)
                stack.append(sign)

                # Reset operand and result, as if new evaluation begins for the new sub-expression
                sign = 1
                result = 0

            elif ch == ')':
                # Evaluate the expression to the left
                result += sign * operand

                # ')' marks end of expression within a set of parenthesis
                # Its result is multiplied with sign on top of stack
                result *= stack.pop()    # stack pop gives us the sign

                # Then add to the next operand on the top.
                result += stack.pop()    # stack pop now gives the previous result

                # Reset the operand
                operand = 0

        return result + sign * operand