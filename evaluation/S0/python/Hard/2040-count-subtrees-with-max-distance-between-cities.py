# Source: https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/   |   Difficulty: Hard
#
# Problem Description:
# There are n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i] = [ui, vi] represents a bidirectional edge between cities ui and vi. There exists a unique path between each pair of cities. In other words, the cities form a tree.
#
# A subtree is a subset of cities where every city is reachable from every other city in the subset, where the path between each pair passes through only the cities from the subset. Two subtrees are different if there is a city in one subtree that is not present in the other.
#
# For each d from 1 to n-1, find the number of subtrees in which the maximum distance between any two cities in the subtree is equal to d.
#
# Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees in which the maximum distance between any two cities is equal to d.
#
# Notice that the distance between the two cities is the number of edges in the path between them.
#
# Example:
# Input: n = 4, edges = [[1,2],[2,3],[2,4]]
# Output: [3,4,0]
# Explanation:
# The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
# The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
# No subtree has two nodes where the max distance between them is 3.
#
# Constraints:
# 2 <= n <= 15
# 	edges.length == n-1
# 	edges[i].length == 2
# 	1 <= ui, vi <= n
# 	All pairs (ui, vi) are distinct.
#

class Solution(object):
    def countSubgraphsForEachDiameter(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def bfs(start, nodes_set):
            visited = set()
            queue = deque([(start, 0)])
            max_dist = 0

            while queue:
                node, dist = queue.popleft()
                visited.add(node)
                max_dist = max(max_dist, dist)

                for neighbor in graph[node]:
                    if neighbor in nodes_set and neighbor not in visited:
                        queue.append((neighbor, dist + 1))

            return max_dist

        result = [0] * (n - 1)

        for mask in range(1, 1 << n):
            nodes_set = {i + 1 for i in range(n) if mask & (1 << i)}
            if len(nodes_set) < 2:
                continue

            start_node = next(iter(nodes_set))
            diameter = bfs(start_node, nodes_set)

            if all(bfs(node, nodes_set) <= diameter for node in nodes_set):
                result[diameter - 1] += 1

        return result