# Source: https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/   |   Difficulty: Hard
#
# Problem Description:
# You are given a valid boolean expression as a string expression consisting of the characters '1','0','&' (bitwise AND operator),'|' (bitwise OR operator),'(', and ')'.
#
#
# 	For example, "()1|1" and "(1)&()" are not valid while "1", "(((1))|(0))", and "1|(0&(1))" are valid expressions.
#
#
# Return the minimum cost to change the final value of the expression.
#
#
# 	For example, if expression = "1|1|(0&0)&1", its value is 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1. We want to apply operations so that the new expression evaluates to 0.
#
#
# The cost of changing the final value of an expression is the number of operations performed on the expression. The types of operations are described as follows:
#
#
# 	Turn a '1' into a '0'.
# 	Turn a '0' into a '1'.
# 	Turn a '&' into a '|'.
# 	Turn a '|' into a '&'.
#
#
# Note: '&' does not take precedence over '|' in the order of calculation. Evaluate parentheses first, then in left-to-right order.
#
# Example:
# Input: expression = "1&(0|1)"
# Output: 1
# Explanation: We can turn "1&(0|1)" into "1&(0&1)" by changing the '|' to a '&' using 1 operation.
# The new expression evaluates to 0.
#
# Constraints:
# 1 <= expression.length <= 105
# 	expression only contains '1','0','&','|','(', and ')'
# 	All parentheses are properly matched.
# 	There will be no empty parentheses (i.e: "()" is not a substring of expression).
#

class Solution(object):
    def minOperationsToFlip(self, expression):
        """
        :type expression: str
        :rtype: int
        """
        def helper(s, i):
            operands = []
            operators = []
            
            def compute():
                right = operands.pop()
                left = operands.pop()
                op = operators.pop()
                
                if op == '&':
                    val = left[0] & right[0]
                    to_flip = min(left[1] + right[1], left[0] + right[0] + 1)
                else:
                    val = left[0] | right[0]
                    to_flip = min(left[1] + right[1], (1 - left[0]) + (1 - right[0]) + 1)
                
                operands.append((val, to_flip))
            
            while i < len(s):
                char = s[i]
                
                if char in '01':
                    operands.append((int(char), 1))
                elif char in '&|':
                    operators.append(char)
                elif char == '(':
                    sub_expr, i = helper(s, i + 1)
                    operands.append(sub_expr)
                elif char == ')':
                    break
                
                while len(operators) > 0 and len(operands) >= 2:
                    compute()
                
                i += 1
            
            while len(operators) > 0:
                compute()
            
            return operands[0], i
        
        result, _ = helper(expression, 0)
        return result[1]