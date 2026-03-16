# Source: https://leetcode.com/problems/k-th-nearest-obstacle-queries/   |   Difficulty: Medium
#
# Problem Description:
# There is an infinite 2D plane.
#
# You are given a positive integer k. You are also given a 2D array queries, which contains the following queries:
#
#
# 	queries[i] = [x, y]: Build an obstacle at coordinate (x, y) in the plane. It is guaranteed that there is no obstacle at this coordinate when this query is made.
#
#
# After each query, you need to find the distance of the kth nearest obstacle from the origin.
#
# Return an integer array results where results[i] denotes the kth nearest obstacle after query i, or results[i] == -1 if there are less than k obstacles.
#
# Note that initially there are no obstacles anywhere.
#
# The distance of an obstacle at coordinate (x, y) from the origin is given by |x| + |y|.
#
# Example:
# Input: queries = [[1,2],[3,4],[2,3],[-3,0]], k = 2
#
# Output: [-1,7,5,3]
#
# Explanation:
#
#
# 	Initially, there are 0 obstacles.
# 	After queries[0], there are less than 2 obstacles.
# 	After queries[1], there are obstacles at distances 3 and 7.
# 	After queries[2], there are obstacles at distances 3, 5, and 7.
# 	After queries[3], there are obstacles at distances 3, 3, 5, and 7.
#
# Constraints:
# 1 <= queries.length <= 2 * 105
# 	All queries[i] are unique.
# 	-109 <= queries[i][0], queries[i][1] <= 109
# 	1 <= k <= 105
#
# Helpful references (internal KB):
# - Manhattan Distance (geometry, number, coordinate-compress)
#   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
#   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
#   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
#   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
#   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
# - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
#   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
#   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
#   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
#   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
#   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def resultsArray(self, queries, k):
        """
        :type queries: List[List[int]]
        :type k: int
        :rtype: List[int]
        """
        import heapq
        
        # Step 1: Min-heap to store distances of obstacles
        min_heap = []
        results = []
        
        for x, y in queries:
            distance = abs(x) + abs(y)
            heapq.heappush(min_heap, distance)
            
            # Step 2: If there are at least k obstacles, get the kth nearest
            if len(min_heap) >= k:
                kth_nearest = heapq.nsmallest(k, min_heap)[-1]
                results.append(kth_nearest)
            else:
                results.append(-1)
        
        return results