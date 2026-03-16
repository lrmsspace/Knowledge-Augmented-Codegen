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

class Solution {
    public int[] hitBricks(int[][] grid, int[][] hits) {
        int m = grid.length, n = grid[0].length;
        int size = m * n;
        int[] parent = new int[size + 1];
        int[] rank = new int[size + 1];
        int[] count = new int[size + 1];

        for (int i = 0; i <= size; i++) {
            parent[i] = i;
            rank[i] = 0;
            count[i] = 1;
        }

        int[][] copy = new int[m][n];
        for (int i = 0; i < m; i++) {
            System.arraycopy(grid[i], 0, copy[i], 0, n);
        }

        for (int[] hit : hits) {
            int x = hit[0], y = hit[1];
            if (copy[x][y] == 1) {
                copy[x][y] = 0;
            }
        }

        for (int j = 0; j < n; j++) {
            if (copy[0][j] == 1) {
                union(parent, rank, count, j, size);
            }
        }

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (copy[i][j] == 1) {
                    for (int[] dir : directions) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && copy[ni][nj] == 1) {
                            union(parent, rank, count, i * n + j, ni * n + nj);
                        }
                    }
                }
            }
        }

        int hitsLen = hits.length;
        int[] result = new int[hitsLen];

        for (int i = hitsLen - 1; i >= 0; i--) {
            int x = hits[i][0], y = hits[i][1];
            if (grid[x][y] == 0) {
                continue;
            }

            int prevTopCount = count[find(parent, size)];
            for (int[] dir : directions) {
                int ni = x + dir[0], nj = y + dir[1];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && copy[ni][nj] == 1) {
                    union(parent, rank, count, x * n + y, ni * n + nj);
                }
            }
            if (x == 0) {
                union(parent, rank, count, y, size);
            }
            int newTopCount = count[find(parent, size)];
            result[i] = Math.max(0, newTopCount - prevTopCount - 1);
            copy[x][y] = 1;
        }
        return result;  
    }
}
