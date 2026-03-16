# Source: https://leetcode.com/problems/beautiful-arrangement/   |   Difficulty: Medium
#
# Problem Description:
# Suppose you have n integers labeled 1 through n. A permutation of those n integers perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n), either of the following is true:
#
#
# 	perm[i] is divisible by i.
# 	i is divisible by perm[i].
#
#
# Given an integer n, return the number of the beautiful arrangements that you can construct.
#
# Example:
# Input: n = 2
# Output: 2
# Explanation: 
# The first beautiful arrangement is [1,2]:
#     - perm[1] = 1 is divisible by i = 1
#     - perm[2] = 2 is divisible by i = 2
# The second beautiful arrangement is [2,1]:
#     - perm[1] = 2 is divisible by i = 1
#     - i = 2 is divisible by perm[2] = 1
#
# Constraints:
# 1 <= n <= 15
#

class Solution(object):
    def countArrangement(self, n):
        """
        :type n: int
        :rtype: int
        """
        def backtrack(i, visited):
            if i > n:
                return 1
            count = 0
            for num in range(1, n + 1):
                if not visited[num] and (num % i == 0 or i % num == 0):
                    visited[num] = True
                    count += backtrack(i + 1, visited)
                    visited[num] = False
            return count

        visited = [False] * (n + 1)
        return backtrack(1, visited)