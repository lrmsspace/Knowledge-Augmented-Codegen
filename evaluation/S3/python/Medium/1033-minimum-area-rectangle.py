# Source: https://leetcode.com/problems/minimum-area-rectangle/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
#
# Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
#
# Example:
# Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
# Output: 4
#
# Constraints:
# 1 <= points.length <= 500
# 	points[i].length == 2
# 	0 <= xi, yi <= 4 * 104
# 	All the given points are unique.
#
# Helpful references (internal KB):
# - Ordered Set - Python (ds, hashing)
#   • When to use: When you need a collection of unique items where the order of insertion must be preserved, allowing for efficient membership testing and iteration in that specific order.
#   • Idea: An ordered set stores unique elements while maintaining their original insertion order. It provides O(1) average time complexity for additions, deletions, and membership checks, typically implemented using a hash table combined with a linked list.
#   • Invariants: Every element within the set is unique.; The sequence of elements during iteration strictly follows their initial insertion order.
#   • Tips: In Python 3.7+, standard `dict`s maintain insertion order, effectively serving as ordered sets.; Use `collections.OrderedDict` for older Python versions or explicit semantic clarity.
#   • Pitfalls: Order is based on insertion, not value-based sorting; do not confuse the two.; Modifying an element's hash value while it's in the set can lead to undefined behavior.
# - Hash Tables (array, number, string, hashing)
#   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
#   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
#   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
#   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
#   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
# - Ordered Set - Python (ds, hashing)
#   • When to use: Use when you need a collection of unique items that also preserves the order in which items were first added. It's ideal for scenarios requiring both set-like behavior and predictable iteration order.
#   • Idea: An ordered set is a data structure that stores unique elements while maintaining their insertion order. It combines the O(1) average-case time complexity for additions, deletions, and lookups of a hash set with the ordered iteration of a list.
#   • Invariants: All elements within the ordered set are unique.; The iteration order of elements matches their original insertion order.
#   • Tips: Install via `pip install ordered_set` for Python environments.; Leverage for scenarios requiring both uniqueness and order preservation.
#   • Pitfalls: Not a built-in Python type; requires external module installation.; Performance might be marginally slower than a standard `set` due to order maintenance overhead.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minAreaRect(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        point_set = set(map(tuple, points))  # Convert list of lists to set of tuples for O(1) lookups
        min_area = float('inf')

        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                p1, p2 = points[i], points[j]
                if p1[0] != p2[0] and p1[1] != p2[1]:  # Ensure p1 and p2 are diagonal corners
                    # Check if the other two corners of the rectangle exist
                    if (p1[0], p2[1]) in point_set and (p2[0], p1[1]) in point_set:
                        area = abs(p1[0] - p2[0]) * abs(p1[1] - p2[1])
                        min_area = min(min_area, area)

        return min_area if min_area != float('inf') else 0