# Source: https://leetcode.com/problems/detonate-the-maximum-bombs/   |   Difficulty: Medium
#
# Problem Description:
# You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
#
# The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.
#
# You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
#
# Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.
#
# Example:
# Input: bombs = [[2,1,3],[6,1,4]]
# Output: 2
# Explanation:
# The above figure shows the positions and ranges of the 2 bombs.
# If we detonate the left bomb, the right bomb will not be affected.
# But if we detonate the right bomb, both bombs will be detonated.
# So the maximum bombs that can be detonated is max(1, 2) = 2.
#
# Constraints:
# 1 <= bombs.length <= 100
# 	bombs[i].length == 3
# 	1 <= xi, yi, ri <= 105
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Finding common tangents to two circles (geometry, number, enumeration, simulation)
#   • When to use: When needing to find lines that are tangent to two given circles simultaneously. This method is suitable for problems requiring precise geometric line calculations.
#   • Idea: This algorithm finds common tangent lines to two circles by formulating the problem as a system of algebraic equations based on distance constraints. It involves solving a quadratic equation for line coefficients, typically resulting in constant time complexity after initial setup.
#   • Invariants: The distance from the line ax + by + c = 0 to the first circle's center is r1.; The distance from the line ax + by + c = 0 to the second circle's center is r2.
#   • Tips: Normalize the line equation (a^2 + b^2 = 1) to ensure unique representations.; Shift one circle to the origin for simpler calculations, then shift the resulting lines back.
#   • Pitfalls: Forgetting to normalize the line equation can lead to non-unique solutions.; Incorrectly handling the modulus signs (±r1, ±r2) can miss valid tangents.
# - Finding Bridges Online (graph, ds, union-find, counting)
#   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
#   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
#   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
#   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
#   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumDetonation(self, bombs):
        """
        :type bombs: List[List[int]]
        :rtype: int
        """
        n = len(bombs)
        graph = [[] for _ in range(n)]

        # Build the graph based on bomb ranges
        for i in range(n):
            x1, y1, r1 = bombs[i]
            for j in range(n):
                if i != j:
                    x2, y2, r2 = bombs[j]
                    if (x1 - x2) ** 2 + (y1 - y2) ** 2 <= r1 ** 2:
                        graph[i].append(j)

        def dfs(node, visited):
            visited.add(node)
            count = 1
            for neighbor in graph[node]:
                if neighbor not in visited:
                    count += dfs(neighbor, visited)
            return count

        max_detonations = 0
        for i in range(n):
            visited = set()
            max_detonations = max(max_detonations, dfs(i, visited))

        return max_detonations