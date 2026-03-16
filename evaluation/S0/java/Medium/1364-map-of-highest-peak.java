// Source: https://leetcode.com/problems/map-of-highest-peak/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer matrix isWater of size m x n that represents a map of land and water cells.
//
//
// 	If isWater[i][j] == 0, cell (i, j) is a land cell.
// 	If isWater[i][j] == 1, cell (i, j) is a water cell.
//
//
// You must assign each cell a height in a way that follows these rules:
//
//
// 	The height of each cell must be non-negative.
// 	If the cell is a water cell, its height must be 0.
// 	Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
//
// Find an assignment of heights such that the maximum height in the matrix is maximized.
//
// Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
//
// Example:
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
//
// Constraints:
// m == isWater.length
// 	n == isWater[i].length
// 	1 <= m, n <= 1000
// 	isWater[i][j] is 0 or 1.
// 	There is at least one water cell.
//
//
//  
// Note: This question is the same as 542: https://leetcode.com/problems/01-matrix/
//

class Solution {
    public int[][] highestPeak(int[][] isWater) {
        int m = isWater.length;
        int n = isWater[0].length;
        int[][] height = new int[m][n];
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new LinkedList<>();

        // Initialize the queue with all water cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isWater[i][j] == 1) {
                    queue.offer(new int[]{i, j});
                    visited[i][j] = true;
                }
            }
        }

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int currentHeight = 0;

        // Perform BFS
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] cell = queue.poll();
                int x = cell[0];
                int y = cell[1];
                height[x][y] = currentHeight;

                for (int[] dir : directions) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
                        visited[newX][newY] = true;
                        queue.offer(new int[]{newX, newY});
                    }
                }
            }
            currentHeight++;
        }

        return height;          
    }
}
