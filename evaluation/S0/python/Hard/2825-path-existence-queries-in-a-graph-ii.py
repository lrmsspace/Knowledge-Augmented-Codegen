# Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
#
# You are also given an integer array nums of length n and an integer maxDiff.
#
# An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
#
# You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.
#
# Return an array answer, where answer[i] is the result of the ith query.
#
# Note: The edges between the nodes are unweighted.
#
# Example:
# Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
#
# Output: [1,1]
#
# Explanation:
#
# The resulting graph is:
#
#
#
#
# 	
# 		
# 			Query
# 			Shortest Path
# 			Minimum Distance
# 		
# 		
# 			[0, 3]
# 			0 → 3
# 			1
# 		
# 		
# 			[2, 4]
# 			2 → 4
# 			1
# 		
# 	
#
#
# Thus, the output is [1, 1].
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	0 <= nums[i] <= 105
# 	0 <= maxDiff <= 105
# 	1 <= queries.length <= 105
# 	queries[i] == [ui, vi]
# 	0 <= ui, vi < n
#

class Solution(object):
    def pathExistenceQueries(self, n, nums, maxDiff, queries):
        """
        :type n: int
        :type nums: List[int]
        :type maxDiff: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for i in range(n):
            for j in range(i + 1, n):
                if abs(nums[i] - nums[j]) <= maxDiff:
                    graph[i].append(j)
                    graph[j].append(i)

        def bfs(start, end):
            visited = set()
            queue = deque([(start, 0)])
            visited.add(start)

            while queue:
                node, dist = queue.popleft()
                if node == end:
                    return dist
                for neighbor in graph[node]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append((neighbor, dist + 1))
            return -1

        results = []
        for u, v in queries:
            results.append(bfs(u, v))

        return results