# Source: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/   |   Difficulty: Hard
#
# Problem Description:
# A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.
#
# The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.
#
# Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.
#
# Example:
# Input: favorite = [2,2,1,2]
# Output: 3
# Explanation:
# The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
# All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
# Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
# The maximum number of employees that can be invited to the meeting is 3.
#
# Constraints:
# n == favorite.length
# 	2 <= n <= 105
# 	0 <= favorite[i] <= n - 1
# 	favorite[i] != i
#

class Solution(object):
    def maximumInvitations(self, favorite):
        """
        :type favorite: List[int]
        :rtype: int
        """
        n = len(favorite)
        visited = [False] * n
        max_cycle = 0
        pair_sum = 0
        depth = [0] * n

        def dfs(node):
            nonlocal max_cycle, pair_sum
            stack = []
            current = node
            while True:
                if visited[current]:
                    if current in stack:
                        cycle_length = len(stack) - stack.index(current)
                        max_cycle = max(max_cycle, cycle_length)
                    return
                visited[current] = True
                stack.append(current)
                next_node = favorite[current]
                if favorite[next_node] == current:
                    depth[current] = max(depth[current], depth[next_node] + 1)
                    pair_sum += depth[next_node] + 1
                    return
                current = next_node

        for i in range(n):
            if not visited[i]:
                dfs(i)

        return max(max_cycle, pair_sum)