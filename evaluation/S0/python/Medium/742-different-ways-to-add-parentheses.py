# Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
#
# The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
#
# Example:
# Input: expression = "2-1-1"
# Output: [0,2]
# Explanation:
# ((2-1)-1) = 0 
# (2-(1-1)) = 2
#
# Constraints:
# 1 <= expression.length <= 20
# 	expression consists of digits and the operator '+', '-', and '*'.
# 	All the integer values in the input expression are in the range [0, 99].
# 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
#

class Solution(object):
    def diffWaysToCompute(self, expression):
        """
        :type expression: str
        :rtype: List[int]
        """
        if expression.isdigit():
            return [int(expression)]
        
        results = []
        for i, char in enumerate(expression):
            if char in "+-*":
                left_results = self.diffWaysToCompute(expression[:i])
                right_results = self.diffWaysToCompute(expression[i+1:])
                
                for left in left_results:
                    for right in right_results:
                        if char == '+':
                            results.append(left + right)
                        elif char == '-':
                            results.append(left - right)
                        elif char == '*':
                            results.append(left * right)
        
        return results