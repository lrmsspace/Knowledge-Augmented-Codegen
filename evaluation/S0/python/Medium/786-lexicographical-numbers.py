# Source: https://leetcode.com/problems/lexicographical-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
#
# You must write an algorithm that runs in O(n) time and uses O(1) extra space.
#
# Example:
# Input: n = 13
# Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
#
# Constraints:
# 1 <= n <= 5 * 104
#

class Solution(object):
    def lexicalOrder(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        result = []
        
        def dfs(current):
            if current > n:
                return
            result.append(current)
            for i in range(10):
                next_num = current * 10 + i
                if next_num > n:
                    break
                dfs(next_num)
        
        for i in range(1, 10):
            if i > n:
                break
            dfs(i)
        
        return result