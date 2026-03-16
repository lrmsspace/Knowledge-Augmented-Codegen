# Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
#
# Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
#
# Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
#
# Example:
# Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
# Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
# Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
#
# Constraints:
# 1 <= trees.length <= 3000
# 	trees[i].length == 2
# 	0 <= xi, yi <= 100
# 	All the given positions are unique.
#
# Helpful references (internal KB):
# - Convex Hull construction (geometry, array, enumeration)
#   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
#   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
#   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
#   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
#   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
# - Convex Hull construction (geometry, array, stack, sweep-line, monotonic-stack)
#   • When to use: When you need to find the smallest convex polygon enclosing a given set of points. It's used for problems requiring the outermost boundary of a point set.
#   • Idea: Convex Hull construction algorithms, like Graham Scan or Monotone Chain, find the smallest convex polygon that encloses a given set of points. These algorithms typically have a time complexity of O(N log N) due to sorting.
#   • Invariants: The points currently on the stack form a convex chain in the desired direction.; For any three consecutive points A, B, C on the stack, the turn from AB to BC maintains convexity.
#   • Tips: Use an orientation test (cross product) to determine if points make a clockwise or counter-clockwise turn.; Handle collinear points carefully, especially if they need to be included in the hull.
#   • Pitfalls: Incorrectly handling collinear points can lead to an incomplete or incorrect hull.; Floating-point precision issues can affect orientation tests, leading to wrong turns.
# - Convex Hull construction (geometry, array, stack, sweep-line)
#   • When to use: Used to find the smallest convex polygon that encloses a given set of points. It is applied when the outer boundary of a point set is required.
#   • Idea: Constructs the smallest convex polygon containing all given points, typically using algorithms like Graham's scan or Monotone Chain. These algorithms achieve an optimal time complexity of O(N log N).
#   • Invariants: The points on the stack, from bottom to top, form a convex chain.; For any three consecutive points A, B, C on the stack (A below B, B below C), the turn from A to B to C is always a left turn or straight.
#   • Tips: Handle collinear points carefully, especially during sorting and turn checks.; Choose a robust orientation test (e.g., cross product) to determine turns.
#   • Pitfalls: Incorrectly handling collinear points can lead to non-convex hulls or missing points.; Floating-point precision issues can cause incorrect turn determinations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def outerTrees(self, trees):
        """
        :type trees: List[List[int]]
        :rtype: List[List[int]]
        """
        # 1. Sort the points by x-coordinate (and y-coordinate for ties)
        trees.sort(key=lambda x: (x[0], x[1]))

        # 2. Build the lower hull
        lower = []
        for p in trees:
            while len(lower) >= 2 and self.cross(lower[-2], lower[-1], p) < 0:
                lower.pop()
            lower.append(p)

        # 3. Build the upper hull
        upper = []
        for p in reversed(trees):
            while len(upper) >= 2 and self.cross(upper[-2], upper[-1], p) < 0:
                upper.pop()
            upper.append(p)

        # 4. Concatenate lower and upper hull to get the full hull
        # The last point of each half is omitted because it's repeated at the beginning of the other half
        return list(set(tuple(p) for p in lower[:-1] + upper[:-1]))