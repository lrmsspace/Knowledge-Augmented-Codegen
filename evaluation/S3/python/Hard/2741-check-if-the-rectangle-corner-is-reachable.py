# Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
#
# There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
#
# Return true if such a path exists, and false otherwise.
#
# Example:
# Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
#
# Output: true
#
# Explanation:
#
#
#
# The black curve shows a possible path between (0, 0) and (3, 4).
#
# Constraints:
# 3 <= xCorner, yCorner <= 109
# 	1 <= circles.length <= 1000
# 	circles[i].length == 3
# 	1 <= xi, yi, ri <= 109
#
# Helpful references (internal KB):
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
#   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
#   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
# - Disjoint Set Union (ds, linked-list, union-find, dfs)
#   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
#   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
#   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def canReachCorner(self, xCorner, yCorner, circles):
        """
        :type xCorner: int
        :type yCorner: int
        :type circles: List[List[int]]
        :rtype: bool
        """
        from collections import deque

        # Directions for moving up, down, left, right
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        # Function to check if a point is inside any circle
        def is_inside_circle(x, y):
            for cx, cy, r in circles:
                if (x - cx) ** 2 + (y - cy) ** 2 < r ** 2:
                    return True
            return False
        
        # BFS initialization
        queue = deque([(0, 0)])
        visited = set((0, 0))
        
        while queue:
            x, y = queue.popleft()
            
            # Check if we reached the target corner
            if (x, y) == (xCorner, yCorner):
                return True
            
            # Explore neighbors
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                
                # Check boundaries and if the point is not inside any circle
                if 0 <= nx <= xCorner and 0 <= ny <= yCorner and (nx, ny) not in visited and not is_inside_circle(nx, ny):
                    visited.add((nx, ny))
                    queue.append((nx, ny))
        
        return False