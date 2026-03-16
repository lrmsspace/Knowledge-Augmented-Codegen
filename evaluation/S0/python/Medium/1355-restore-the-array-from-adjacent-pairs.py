# Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
#
# Problem Description:
# There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
#
# You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
#
# It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
#
# Return the original array nums. If there are multiple solutions, return any of them.
#
# Example:
# Input: adjacentPairs = [[2,1],[3,4],[3,2]]
# Output: [1,2,3,4]
# Explanation: This array has all its adjacent pairs in adjacentPairs.
# Notice that adjacentPairs[i] may not be in left-to-right order.
#
# Constraints:
# nums.length == n
# 	adjacentPairs.length == n - 1
# 	adjacentPairs[i].length == 2
# 	2 <= n <= 105
# 	-105 <= nums[i], ui, vi <= 105
# 	There exists some nums that has adjacentPairs as its pairs.
#

class Solution(object):
    def restoreArray(self, adjacentPairs):
        """
        :type adjacentPairs: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        # Build the graph
        graph = defaultdict(list)
        for u, v in adjacentPairs:
            graph[u].append(v)
            graph[v].append(u)

        # Find the starting point (a node with only one neighbor)
        start = None
        for node, neighbors in graph.items():
            if len(neighbors) == 1:
                start = node
                break

        # Reconstruct the array using BFS/DFS
        result = []
        visited = set()
        queue = deque([start])

        while queue:
            node = queue.popleft()
            if node in visited:
                continue
            visited.add(node)
            result.append(node)

            for neighbor in graph[node]:
                if neighbor not in visited:
                    queue.append(neighbor)

        return result