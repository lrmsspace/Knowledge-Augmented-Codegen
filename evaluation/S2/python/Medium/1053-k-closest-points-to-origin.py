# Source: https://leetcode.com/problems/k-closest-points-to-origin/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
#
# The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
#
# You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
#
# Example:
# Input: points = [[1,3],[-2,2]], k = 1
# Output: [[-2,2]]
# Explanation:
# The distance between (1, 3) and the origin is sqrt(10).
# The distance between (-2, 2) and the origin is sqrt(8).
# Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
# We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
#
# Constraints:
# 1 <= k <= points.length <= 104
# 	-104 <= xi, yi <= 104
#
# Helpful references (internal KB):
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
# - Circle-Line Intersection (geometry, number, enumeration, simulation)
#   • When to use: Use this algorithm to find the intersection points between a circle and a line, especially when numerical stability is a concern. It efficiently determines zero, one, or two intersection points.
#   • Idea: This algorithm finds the intersection points of a circle and a line by using geometric properties like distances and vectors, avoiding direct algebraic system solving. It determines zero, one, or two intersection points in constant time, O(1).
#   • Invariants: The distance from the origin to the line, d0, is always correctly calculated as |C| / sqrt(A^2 + B^2).; The point (x0, y0) is always the closest point on the line Ax+By+C=0 to the origin (0,0).
#   • Tips: Translate the circle to the origin for simplified calculations, adjusting the line equation accordingly.; Use the distance from the origin to the line to quickly determine the number of intersection points.
#   • Pitfalls: Floating point precision errors can accumulate, especially with very small or large coordinates.; Incorrectly handling edge cases where the line is tangent to the circle or passes through the origin.
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def kClosest(self, points, k):
        """
        :type points: List[List[int]]
        :type k: int
        :rtype: List[List[int]]
        """
        import heapq
        
        def distance(point):
            return point[0] ** 2 + point[1] ** 2
        
        min_heap = [(distance(point), point) for point in points]
        heapq.heapify(min_heap)
        
        closest_points = []
        for _ in range(k):
            closest_points.append(heapq.heappop(min_heap)[1])
        
        return closest_points