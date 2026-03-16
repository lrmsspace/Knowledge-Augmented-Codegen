# Source: https://leetcode.com/problems/cheapest-flights-within-k-stops/   |   Difficulty: Medium
#
# Problem Description:
# There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.
#
# You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
#
# Example:
# Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
# Output: 700
# Explanation:
# The graph is shown above.
# The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
# Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
#
# Constraints:
# 1 <= n <= 100
# 	0 <= flights.length <= (n * (n - 1) / 2)
# 	flights[i].length == 3
# 	0 <= fromi, toi < n
# 	fromi != toi
# 	1 <= pricei <= 104
# 	There will not be any multiple flights between two cities.
# 	0 <= src, dst, k < n
# 	src != dst
#

class Solution(object):
    def findCheapestPrice(self, n, flights, src, dst, k):
        """
        :type n: int
        :type flights: List[List[int]]
        :type src: int
        :type dst: int
        :type k: int
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for u, v, price in flights:
            graph[u].append((v, price))

        # Min-heap priority queue: (cost, current_city, stops_remaining)
        pq = [(0, src, k + 1)]
        while pq:
            cost, city, stops = heapq.heappop(pq)

            if city == dst:
                return cost

            if stops > 0:
                for neighbor, price in graph[city]:
                    heapq.heappush(pq, (cost + price, neighbor, stops - 1))

        return -1