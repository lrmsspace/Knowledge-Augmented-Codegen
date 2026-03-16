# Source: https://leetcode.com/problems/min-cost-to-connect-all-points/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
#
# The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
#
# Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.
#
# Example:
# Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
# Output: 20
# Explanation: 
#
# We can connect the points as shown above to get the minimum cost of 20.
# Notice that there is a unique path between every pair of points.
#
# Constraints:
# 1 <= points.length <= 1000
# 	-106 <= xi, yi <= 106
# 	All pairs (xi, yi) are distinct.
#

class Solution(object):
    def minCostConnectPoints(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        import heapq

        n = len(points)
        visited = [False] * n
        min_heap = [(0, 0)]  # (cost, point_index)
        total_cost = 0
        edges_used = 0

        while edges_used < n:
            cost, u = heapq.heappop(min_heap)
            if visited[u]:
                continue
            visited[u] = True
            total_cost += cost
            edges_used += 1

            for v in range(n):
                if not visited[v]:
                    dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1])
                    heapq.heappush(min_heap, (dist, v))

        return total_cost