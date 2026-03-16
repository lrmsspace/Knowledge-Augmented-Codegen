// Source: https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.
//
// Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
//
// Example:
// Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
// Output: 6
// Explanation: 
// The shortest path without eliminating any obstacle is 10.
// The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 40
// 	1 <= k <= m * n
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int shortestPath(int[][] grid, int k) {
        int m = grid.length, n = grid[0].length;
        int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        boolean[][][] visited = new boolean[m][n][k + 1];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, k});
        visited[0][0][k] = true;
        int steps = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] current = queue.poll();
                int x = current[0], y = current[1], remainingK = current[2];

                if (x == m - 1 && y == n - 1) {
                    return steps;
                }

                for (int[] dir : dirs) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];
                    if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                        int newK = remainingK - grid[newX][newY];
                        if (newK >= 0 && !visited[newX][newY][newK]) {
                            visited[newX][newY][newK] = true;
                            queue.offer(new int[]{newX, newY, newK});
                        }
                    }
                }
            }
            steps++;
        }

        return -1;          
    }
}
