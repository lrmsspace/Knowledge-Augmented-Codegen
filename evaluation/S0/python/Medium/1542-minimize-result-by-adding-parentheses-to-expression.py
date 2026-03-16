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

class Solution(object):
    def minimizeResult(self, expression):
        """
        :type expression: str
        :rtype: str
        """
        plus_index = expression.index('+')
        min_value = float('inf')
        result = ""
        
        for i in range(plus_index):
            for j in range(plus_index + 1, len(expression) + 1):
                left_multiplier = int(expression[:i]) if i > 0 else 1
                right_multiplier = int(expression[j:]) if j < len(expression) else 1
                left_number = int(expression[i:plus_index])
                right_number = int(expression[plus_index + 1:j])
                
                current_value = left_multiplier * (left_number + right_number) * right_multiplier
                
                if current_value < min_value:
                    min_value = current_value
                    result = expression[:i] + '(' + expression[i:j] + ')' + expression[j:]
        
        return result