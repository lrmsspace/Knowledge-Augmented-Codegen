# Source: https://leetcode.com/problems/24-game/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
#
# You are restricted with the following rules:
#
#
# 	The division operator '/' represents real division, not integer division.
#
# 	
# 		For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
# 	
# 	
# 	Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
# 	
# 		For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
# 	
# 	
# 	You cannot concatenate numbers together
# 	
# 		For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
# 	
# 	
#
#
# Return true if you can get such expression that evaluates to 24, and false otherwise.
#
# Example:
# Input: cards = [4,1,8,7]
# Output: true
# Explanation: (8-4) * (7-1) = 24
#
# Constraints:
# cards.length == 4
# 	1 <= cards[i] <= 9
#

class Solution(object):
    def judgePoint24(self, cards):
        """
        :type cards: List[int]
        :rtype: bool
        """
        from itertools import permutations, product

        def helper(nums):
            if len(nums) == 1:
                return abs(nums[0] - 24) < 1e-6
            
            for i in range(len(nums)):
                for j in range(len(nums)):
                    if i != j:
                        next_nums = [nums[k] for k in range(len(nums)) if k != i and k != j]
                        for op in ['+', '-', '*', '/']:
                            if op == '+':
                                next_nums.append(nums[i] + nums[j])
                            elif op == '-':
                                next_nums.append(nums[i] - nums[j])
                            elif op == '*':
                                next_nums.append(nums[i] * nums[j])
                            elif op == '/' and nums[j] != 0:
                                next_nums.append(nums[i] / nums[j])
                            if helper(next_nums):
                                return True
                            next_nums.pop()
            return False

        for perm in permutations(cards):
            if helper(list(perm)):
                return True
        return False