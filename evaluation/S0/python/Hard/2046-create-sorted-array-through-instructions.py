# Source: https://leetcode.com/problems/create-sorted-array-through-instructions/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
#
#
# 	The number of elements currently in nums that are strictly less than instructions[i].
# 	The number of elements currently in nums that are strictly greater than instructions[i].
#
#
# For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
#
# Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7
#
# Example:
# Input: instructions = [1,5,6,2]
# Output: 1
# Explanation: Begin with nums = [].
# Insert 1 with cost min(0, 0) = 0, now nums = [1].
# Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
# Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
# Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
# The total cost is 0 + 0 + 0 + 1 = 1.
#
# Constraints:
# 1 <= instructions.length <= 105
# 	1 <= instructions[i] <= 105
#

class Solution(object):
    def createSortedArray(self, instructions):
        """
        :type instructions: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        max_val = max(instructions)
        
        # Binary Indexed Tree (Fenwick Tree) for counting
        BIT = [0] * (max_val + 1)
        
        def update(index):
            while index <= max_val:
                BIT[index] += 1
                index += index & -index
        
        def query(index):
            total = 0
            while index > 0:
                total += BIT[index]
                index -= index & -index
            return total
        
        cost = 0
        for i, num in enumerate(instructions):
            less_count = query(num - 1)
            greater_count = i - query(num)
            cost += min(less_count, greater_count)
            cost %= MOD
            update(num)
        
        return cost