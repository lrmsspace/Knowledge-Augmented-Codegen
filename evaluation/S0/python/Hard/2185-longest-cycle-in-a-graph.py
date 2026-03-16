# Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
#
# The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
#
# Return the length of the longest cycle in the graph. If no cycle exists, return -1.
#
# A cycle is a path that starts and ends at the same node.
#
# Example:
# Input: edges = [3,3,4,2,3]
# Output: 3
# Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
# The length of this cycle is 3, so 3 is returned.
#
# Constraints:
# n == edges.length
# 	2 <= n <= 105
# 	-1 <= edges[i] < n
# 	edges[i] != i
#

class Solution(object):
    def longestCycle(self, edges):
        """
        :type edges: List[int]
        :rtype: int
        """
        n = len(edges)
        visited = [0] * n
        max_cycle_length = -1

        for i in range(n):
            if visited[i]:
                continue

            current = i
            index_map = {}
            step = 0

            while current != -1:
                if visited[current]:
                    break

                if current in index_map:
                    cycle_length = step - index_map[current]
                    max_cycle_length = max(max_cycle_length, cycle_length)
                    break

                index_map[current] = step
                visited[current] = 1
                current = edges[current]
                step += 1

        return max_cycle_length