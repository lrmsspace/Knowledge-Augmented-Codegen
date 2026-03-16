# Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
#
# Problem Description:
# Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
#
# The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
#
# A valid square has four equal sides with positive length and four equal angles (90-degree angles).
#
# Example:
# Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
# Output: true
#
# Constraints:
# p1.length == p2.length == p3.length == p4.length == 2
# 	-104 <= xi, yi <= 104
#
# Helpful references (internal KB):
# - Finding the nearest pair of points (geometry, array, divide-and-conquer)
#   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
#   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
#   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
#   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
#   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
# - Balanced bracket sequences (number, counting)
#   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
#   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
#   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
#   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
#   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def validSquare(self, p1, p2, p3, p4):
        """
        :type p1: List[int]
        :type p2: List[int]
        :type p3: List[int]
        :type p4: List[int]
        :rtype: bool
        """
        def dist_sq(a, b):
            return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

        points = [p1, p2, p3, p4]
        dists = []
        
        for i in range(4):
            for j in range(i + 1, 4):
                dists.append(dist_sq(points[i], points[j]))
        
        dists.sort()
        
        # In a valid square, there should be 4 equal smaller distances (sides)
        # and 2 equal larger distances (diagonals)
        return (dists[0] > 0 and
                dists[0] == dists[1] == dists[2] == dists[3] and
                dists[4] == dists[5] and
                dists[4] > dists[0])