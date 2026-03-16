# Source: https://leetcode.com/problems/validate-stack-sequences/   |   Difficulty: Medium
#
# Problem Description:
# Given two integer arrays pushed and popped each with distinct values, return true if this could have been the result of a sequence of push and pop operations on an initially empty stack, or false otherwise.
#
# Example:
# Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
# Output: true
# Explanation: We might do the following sequence:
# push(1), push(2), push(3), push(4),
# pop() -> 4,
# push(5),
# pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
#
# Constraints:
# 1 <= pushed.length <= 1000
# 	0 <= pushed[i] <= 1000
# 	All the elements of pushed are unique.
# 	popped.length == pushed.length
# 	popped is a permutation of pushed.
#

class Solution(object):
    def validateStackSequences(self, pushed, popped):
        """
        :type pushed: List[int]
        :type popped: List[int]
        :rtype: bool
        """
        stack = []
        j = 0

        for x in pushed:
            stack.append(x)  # push operation
            while stack and stack[-1] == popped[j]:
                stack.pop()  # pop operation
                j += 1

        return j == len(popped)