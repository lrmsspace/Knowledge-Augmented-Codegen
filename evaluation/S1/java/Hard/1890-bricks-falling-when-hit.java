// Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
//
//
// 	It is directly connected to the top of the grid, or
// 	At least one other brick in its four adjacent cells is stable.
//
//
// You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
//
// Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
//
// Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
//
// Example:
// Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
// Output: [2]
// Explanation: Starting with the grid:
// [[1,0,0,0],
//  [1,1,1,0]]
// We erase the underlined brick at (1,0), resulting in the grid:
// [[1,0,0,0],
//  [0,1,1,0]]
// The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
// [[1,0,0,0],
//  [0,0,0,0]]
// Hence the result is [2].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 200
// 	grid[i][j] is 0 or 1.
// 	1 <= hits.length <= 4 * 104
// 	hits[i].length == 2
// 	0 <= xi <= m - 1
// 	0 <= yi <= n - 1
// 	All (xi, yi) are unique.
//
// Helpful references (internal KB):
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] hitBricks(int[][] grid, int[][] hits) {
        int m = grid.length, n = grid[0].length;
        int[] result = new int[hits.length];
        int[][] copy = new int[m][n];
        for (int i = 0; i < m; i++) {
            System.arraycopy(grid[i], 0, copy[i], 0, n);
        }
        for (int[] hit : hits) {
            copy[hit[0]][hit[1]] = 0;
        }
        UnionFind uf = new UnionFind(m * n + 1);
        for (int j = 0; j < n; j++) {
            if (copy[0][j] == 1) {
                uf.union(j, m * n);
            }
        }
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (copy[i][j] == 1) {
                    for (int[] dir : directions) {
                        int x = i + dir[0], y = j + dir[1];
                        if (x >= 0 && x < m && y >= 0 && y < n && copy[x][y] == 1) {
                            uf.union(i * n + j, x * n + y);
                        }
                    }
                }
            }
        }
        for (int k = hits.length - 1; k >= 0; k--) {
            int i = hits[k][0], j = hits[k][1];
            if (grid[i][j] == 0) {
                continue;
            }
            int prevTopConnectedBricks = uf.getSize(m * n);
            if (i == 0) {
                uf.union(j, m * n);
            }
            for (int[] dir : directions) {
                int x = i + dir[0], y = j + dir[1];
                if (x >= 0 && x < m && y >= 0 && y < n && copy[x][y] == 1) {
                    uf.union(i * n + j, x * n + y);
                }
            }
            copy[i][j] = 1;
            int newTopConnectedBricks = uf.getSize(m * n);
            result[k] = Math.max(0, newTopConnectedBricks - prevTopConnectedBricks - 1);
            
        }
        return result;
    }
}
