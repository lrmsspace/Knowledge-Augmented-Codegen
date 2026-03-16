// Source: https://leetcode.com/problems/swim-in-rising-water/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
//
// It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
//
// You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
//
// Example:
// Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] < n2
// 	Each value grid[i][j] is unique.
//

class Solution {
    public int swimInWater(int[][] grid) {
        int n = grid.length;
        int left = grid[0][0];
        int right = n * n - 1;
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (left < right) {
            int mid = left + (right - left) / 2;
            boolean[][] visited = new boolean[n][n];
            Queue<int[]> queue = new LinkedList<>();
            queue.offer(new int[]{0, 0});
            visited[0][0] = true;

            while (!queue.isEmpty()) {
                int[] cell = queue.poll();
                int x = cell[0];
                int y = cell[1];

                for (int[] dir : directions) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if (newX >= 0 && newX < n && newY >= 0 && newY < n &&
                        !visited[newX][newY] && grid[newX][newY] <= mid) {
                        visited[newX][newY] = true;
                        queue.offer(new int[]{newX, newY});
                    }
                }
            }

            if (visited[n - 1][n - 1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;            
    }
}
