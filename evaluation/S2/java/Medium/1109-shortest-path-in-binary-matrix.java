// Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
//
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
//
//
// 	All the visited cells of the path are 0.
// 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
//
//
// The length of a clear path is the number of visited cells of this path.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 2
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
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
    public int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1; // No path if start or end is blocked
        }

        int[][] directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        boolean[][] visited = new boolean[n][n];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0});
        visited[0][0] = true;
        int pathLength = 1;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] cell = queue.poll();
                int x = cell[0], y = cell[1];

                if (x == n - 1 && y == n - 1) {
                    return pathLength; // Reached the destination
                }

                for (int[] dir : directions) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if (isValid(newX, newY, n) && grid[newX][newY] == 0 && !visited[newX][newY]) {
                        visited[newX][newY] = true;
                        queue.offer(new int[]{newX, newY});
                    }
                }
            }
            pathLength++;
        }

        return -1; // No path found         
    }
}
