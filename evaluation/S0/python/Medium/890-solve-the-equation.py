# Source: https://leetcode.com/problems/solve-the-equation/   |   Difficulty: Medium
#
# Problem Description:
# Solve a given equation and return the value of 'x' in the form of a string "x=#value". The equation contains only '+', '-' operation, the variable 'x' and its coefficient. You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.
#
# If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.
#
# Example:
# Input: equation = "x+5-3+x=6+x-2"
# Output: "x=2"
#
# Constraints:
# 3 <= equation.length <= 1000
# 	equation has exactly one '='.
# 	equation consists of integers with an absolute value in the range [0, 100] without any leading zeros, and the variable 'x'.
# 	The input is generated that if there is a single solution, it will be an integer.
#

class Solution(object):
    def solveEquation(self, equation):
        """
        :type equation: str
        :rtype: str
        """
        left, right = equation.split('=')
        
        def parse_expression(expr):
            tokens = []
            num = ''
            sign = 1  # 1 for '+', -1 for '-'
            for char in expr:
                if char in '+-':
                    if num:
                        tokens.append(sign * int(num))
                        num = ''
                    sign = 1 if char == '+' else -1
                else:
                    num += char
            if num:
                tokens.append(sign * int(num))
            return tokens
        
        def evaluate(tokens):
            x_coeff = 0
            const_sum = 0
            for token in tokens:
                if 'x' in str(token):
                    coeff = token.replace('x', '')
                    if coeff == '' or coeff == '+':
                        x_coeff += 1
                    elif coeff == '-':
                        x_coeff -= 1
                    else:
                        x_coeff += int(coeff)
                else:
                    const_sum += token
            return x_coeff, const_sum
        
        left_tokens = parse_expression(left)
        right_tokens = parse_expression(right)
        
        left_x, left_const = evaluate(left_tokens)
        right_x, right_const = evaluate(right_tokens)
        
        total_x = left_x - right_x
        total_const = right_const - left_const
        
        if total_x == 0:
            if total_const == 0:
                return "Infinite solutions"
            else:
                return "No solution"
        else:
            x_value = total_const // total_x
            return f"x={x_value}"