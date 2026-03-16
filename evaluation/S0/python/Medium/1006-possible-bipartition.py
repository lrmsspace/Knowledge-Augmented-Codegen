# Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
#
# Problem Description:
# We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
#
# Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
#
# Example:
# Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
# Output: true
# Explanation: The first group has [1,4], and the second group has [2,3].
#
# Constraints:
# 1 <= n <= 2000
# 	0 <= dislikes.length <= 104
# 	dislikes[i].length == 2
# 	1 <= ai < bi <= n
# 	All the pairs of dislikes are unique.
#

class Solution(object):
    def possibleBipartition(self, n, dislikes):
        """
        :type n: int
        :type dislikes: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for a, b in dislikes:
            graph[a].append(b)
            graph[b].append(a)

        color = {}

        for person in range(1, n + 1):
            if person not in color:
                queue = deque([person])
                color[person] = 0

                while queue:
                    current = queue.popleft()
                    for neighbor in graph[current]:
                        if neighbor not in color:
                            color[neighbor] = 1 - color[current]
                            queue.append(neighbor)
                        elif color[neighbor] == color[current]:
                            return False
        return True