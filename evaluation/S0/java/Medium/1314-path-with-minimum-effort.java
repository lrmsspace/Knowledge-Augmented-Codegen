// Source: https://leetcode.com/problems/path-with-minimum-effort/   |   Difficulty: Medium
//
// Problem Description:
// You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
//
// A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
//
// Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
//
// Example:
// Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
// Output: 2
// Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
// This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
//
// Constraints:
// rows == heights.length
// 	columns == heights[i].length
// 	1 <= rows, columns <= 100
// 	1 <= heights[i][j] <= 106
//

class Solution {
    public int minimumEffortPath(int[][] heights) {
        int rows = heights.length;
        int cols = heights[0].length;
        int left = 0, right = 1_000_000; // max height difference can be 10^6

        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        while (left < right) {
            int mid = left + (right - left) / 2;

            boolean[][] visited = new boolean[rows][cols];
            Queue<int[]> queue = new LinkedList<>();
            queue.offer(new int[]{0, 0});
            visited[0][0] = true;

            while (!queue.isEmpty()) {
                int[] cell = queue.poll();
                int r = cell[0], c = cell[1];

                for (int[] dir : directions) {
                    int newRow = r + dir[0];
                    int newCol = c + dir[1];

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                            !visited[newRow][newCol] &&
                            Math.abs(heights[newRow][newCol] - heights[r][c]) <= mid) {
                        visited[newRow][newCol] = true;
                        queue.offer(new int[]{newRow, newCol});
                    }
                }
            }

            if (visited[rows - 1][cols - 1]) {
                right = mid; // try for a smaller maximum effort
            } else {
                left = mid + 1; // increase the effort
            }
        }

        return left;            
    }
}
