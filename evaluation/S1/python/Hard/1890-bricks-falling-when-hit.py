# Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
#
#
# 	It is directly connected to the top of the grid, or
# 	At least one other brick in its four adjacent cells is stable.
#
#
# You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
#
# Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
#
# Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
#
# Example:
# Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
# Output: [2]
# Explanation: Starting with the grid:
# [[1,0,0,0],
#  [1,1,1,0]]
# We erase the underlined brick at (1,0), resulting in the grid:
# [[1,0,0,0],
#  [0,1,1,0]]
# The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
# [[1,0,0,0],
#  [0,0,0,0]]
# Hence the result is [2].
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 200
# 	grid[i][j] is 0 or 1.
# 	1 <= hits.length <= 4 * 104
# 	hits[i].length == 2
# 	0 <= xi <= m - 1
# 	0 <= yi <= n - 1
# 	All (xi, yi) are unique.
#
# Helpful references (internal KB):
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
# - Range Minimum Query (array, ds, union-find)
#   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
#   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
#   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
#   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
#   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
# - The Inclusion-Exclusion Principle (array, number, counting, sieve)
#   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
#   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
#   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
#   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
#   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def hitBricks(self, grid, hits):
        """
        :type grid: List[List[int]]
        :type hits: List[List[int]]
        :rtype: List[int]
        """
        m, n = len(grid), len(grid[0])
        copy = [row[:] for row in grid]
        for x, y in hits:
            copy[x][y] = 0

        def neighbors(x, y):
            for dx, dy in [[1, 0], [-1, 0], [0, 1], [0, -1]]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n:
                    yield nx, ny

        def dfs(x, y):
            count = 1
            copy[x][y] = 2
            for nx, ny in neighbors(x, y):
                if copy[nx][ny] == 1:
                    count += dfs(nx, ny)
            return count

        for j in range(n):
            if copy[0][j] == 1:
                dfs(0, j)

        res = []
        for x, y in reversed(hits):
            if grid[x][y] == 0:
                res.append(0)
                continue
            copy[x][y] = 1
            stable = any(copy[nx][ny] == 2 for nx, ny in neighbors(x, y))
            if stable:
                res.append(dfs(x, y) - 1)
            else:
                res.append(0)

        return res[::-1]