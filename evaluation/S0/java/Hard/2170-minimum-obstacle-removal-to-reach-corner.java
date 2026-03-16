// Source: https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
//
//
// 	0 represents an empty cell,
// 	1 represents an obstacle that may be removed.
//
//
// You can move up, down, left, or right from and to an empty cell.
//
// Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
//
// Example:
// Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
// Output: 2
// Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
// It can be shown that we need to remove at least 2 obstacles, so we return 2.
// Note that there may be other ways to remove 2 obstacles to create a path.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

class Solution {
    public int minimumObstacles(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[][] dist = new int[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[0][0] = 0;

        Deque<int[]> deque = new ArrayDeque<>();
        deque.offerFirst(new int[]{0, 0});

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!deque.isEmpty()) {
            int[] cell = deque.pollFirst();
            int x = cell[0];
            int y = cell[1];

            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];

                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    int newDist = dist[x][y] + grid[newX][newY];
                    if (newDist < dist[newX][newY]) {
                        dist[newX][newY] = newDist;
                        if (grid[newX][newY] == 1) {
                            deque.offerLast(new int[]{newX, newY});
                        } else {
                            deque.offerFirst(new int[]{newX, newY});
                        }
                    }
                }
            }
        }

        return dist[m - 1][n - 1];          
    }
}
