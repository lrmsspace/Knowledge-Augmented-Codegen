# Source: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/   |   Difficulty: Medium
#
# Problem Description:
# There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.
#
# Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.
#
# Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.
#
# Example:
# Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
# Output: 3
# Explanation: The figure above describes the graph. 
# The neighboring cities at a distanceThreshold = 4 for each city are:
# City 0 -> [City 1, City 2] 
# City 1 -> [City 0, City 2, City 3] 
# City 2 -> [City 0, City 1, City 3] 
# City 3 -> [City 1, City 2] 
# Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
#
# Constraints:
# 2 <= n <= 100
# 	1 <= edges.length <= n * (n - 1) / 2
# 	edges[i].length == 3
# 	0 <= fromi < toi < n
# 	1 <= weighti, distanceThreshold <= 10^4
# 	All pairs (fromi, toi) are distinct.
#

class Solution(object):
    def findTheCity(self, n, edges, distanceThreshold):
        """
        :type n: int
        :type edges: List[List[int]]
        :type distanceThreshold: int
        :rtype: int
        """
        import heapq
        graph = [[] for _ in range(n)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        def dijkstra(start):
            distances = [float('inf')] * n
            distances[start] = 0
            heap = [(0, start)]
            
            while heap:
                curr_dist, u = heapq.heappop(heap)
                if curr_dist > distances[u]:
                    continue
                for v, w in graph[u]:
                    if distances[u] + w < distances[v]:
                        distances[v] = distances[u] + w
                        heapq.heappush(heap, (distances[v], v))
            return sum(1 for dist in distances if dist <= distanceThreshold)
        
        min_count = n
        result_city = -1
        
        for city in range(n):
            count = dijkstra(city)
            if count <= min_count:
                min_count = count
                result_city = city
        
        return result_city