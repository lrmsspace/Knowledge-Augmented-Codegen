# Source: https://leetcode.com/problems/parsing-a-boolean-expression/   |   Difficulty: Hard
#
# Problem Description:
# A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:
#
#
# 	't' that evaluates to true.
# 	'f' that evaluates to false.
# 	'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
# 	'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
# 	'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
#
#
# Given a string expression that represents a boolean expression, return the evaluation of that expression.
#
# It is guaranteed that the given expression is valid and follows the given rules.
#
# Example:
# Input: expression = "&(|(f))"
# Output: false
# Explanation: 
# First, evaluate |(f) --> f. The expression is now "&(f)".
# Then, evaluate &(f) --> f. The expression is now "f".
# Finally, return false.
#
# Constraints:
# 1 <= expression.length <= 2 * 104
# 	expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
#

class Solution(object):
    def parseBoolExpr(self, expression):
        """
        :type expression: str
        :rtype: bool
        """
        stack = []
        
        for char in expression:
            if char == ')':
                operands = []
                while stack and stack[-1] != '(':
                    operands.append(stack.pop())
                stack.pop()  # Remove the '('
                
                operator = stack.pop()
                
                if operator == '!':
                    result = 't' if operands[0] == 'f' else 'f'
                elif operator == '&':
                    result = 't' if all(op == 't' for op in operands) else 'f'
                elif operator == '|':
                    result = 't' if any(op == 't' for op in operands) else 'f'
                
                stack.append(result)
            elif char != ',':
                stack.append(char)
        
        return stack[0] == 't'