# Source: https://leetcode.com/problems/expression-add-operators/   |   Difficulty: Hard
#
# Problem Description:
# Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
#
# Note that operands in the returned expressions should not contain leading zeros.
#
# Note that a number can contain multiple digits.
#
# Example:
# Input: num = "123", target = 6
# Output: ["1*2*3","1+2+3"]
# Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
#
# Constraints:
# 1 <= num.length <= 10
# 	num consists of only digits.
# 	-231 <= target <= 231 - 1
#

class Solution(object):
    def addOperators(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """
        res = []
        
        def backtrack(index, path, value, last):
            if index == len(num):
                if value == target:
                    res.append(path)
                return
            
            for i in range(index + 1, len(num) + 1):
                curr_str = num[index:i]
                curr = int(curr_str)
                
                if len(curr_str) > 1 and curr_str[0] == '0':
                    continue
                
                if index == 0:
                    backtrack(i, curr_str, curr, curr)
                else:
                    backtrack(i, path + '+' + curr_str, value + curr, curr)
                    backtrack(i, path + '-' + curr_str, value - curr, -curr)
                    backtrack(i, path + '*' + curr_str, value - last + last * curr, last * curr)
        
        backtrack(0, '', 0, 0)
        return res