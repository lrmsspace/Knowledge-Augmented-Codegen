# Source: https://leetcode.com/problems/minimize-manhattan-distances/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
#
# The distance between two points is defined as their Manhattan distance.
#
# Return the minimum possible value for maximum distance between any two points by removing exactly one point.
#
# Example:
# Input: points = [[3,10],[5,15],[10,2],[4,4]]
#
# Output: 12
#
# Explanation:
#
# The maximum distance after removing each point is the following:
#
#
# 	After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
# 	After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
# 	After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
# 	After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
#
#
# 12 is the minimum possible maximum distance between any two points after removing exactly one point.
#
# Constraints:
# 3 <= points.length <= 105
# 	points[i].length == 2
# 	1 <= points[i][0], points[i][1] <= 108
#
# Helpful references (internal KB):
# - Segment Tree (tree, array, segment-tree, divide-and-conquer)
#   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
#   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
#   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
#   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
#   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Minimum Spanning Trees (graph, greedy)
#   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
#   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
#   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
#   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
#   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumDistance(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        # Step 1: Transform the coordinates
        transformed = [(x + y, x - y) for x, y in points]

        # Step 2: Find the max and min of the transformed coordinates
        max_x_plus_y = max(p[0] for p in transformed)
        min_x_plus_y = min(p[0] for p in transformed)
        max_x_minus_y = max(p[1] for p in transformed)
        min_x_minus_y = min(p[1] for p in transformed)

        # Step 3: Calculate the initial maximum distance
        initial_max_distance = max(max_x_plus_y - min_x_plus_y, max_x_minus_y - min_x_minus_y)

        # Step 4: Check the effect of removing each point
        min_max_distance_after_removal = float('inf')
        
        for x, y in points:
            x_plus_y = x + y
            x_minus_y = x - y
            
            # Calculate new max and min if this point is removed
            new_max_x_plus_y = max(max_x_plus_y, x_plus_y) if x_plus_y != max_x_plus_y else (max(p[0] for p in transformed if p[0] != x_plus_y) if len(transformed) > 1 else float('-inf'))
            new_min_x_plus_y = min(min_x_plus_y, x_plus_y) if x_plus_y != min_x_plus_y else (min(p[0] for p in transformed if p[0] != x_plus_y) if len(transformed) > 1 else float('inf'))
            new_max_x_minus_y = max(max_x_minus_y, x_minus_y) if x_minus_y != max_x_minus_y else (max(p[1] for p in transformed if p[1] != x_minus_y) if len(transformed) > 1 else float('-inf'))
            new_min_x_minus_y = min(min_x_minus_y, x_minus_y) if x_minus_y != min_x_minus_y else (min(p[1] for p in transformed if p[1] != x_minus_y) if len(transformed) > 1 else float('inf'))

            # Calculate the new maximum distance after removal
            new_max_distance = max(new_max_x_plus_y - new_min_x_plus_y, new_max_x_minus_y - new_min_x_minus_y)
            min_max_distance_after_removal = min(min_max_distance_after_removal, new_max_distance)
        return min_max_distance_after_removal   