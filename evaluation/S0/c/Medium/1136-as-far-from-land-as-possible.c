// Source: https://leetcode.com/problems/as-far-from-land-as-possible/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.
//
// The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
//
// Example:
// Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
// Output: 2
// Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

int maxDistance(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int dist[n][n];
    int maxDist = -1;
    
    // Initialize distance array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (grid[i][j] == 1) ? 0 : n * n;
        }
    }
    
    // First pass: top-left to bottom-right
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                if (i > 0) {
                    dist[i][j] = fmin(dist[i][j], dist[i-1][j] + 1);
                }
                if (j > 0) {
                    dist[i][j] = fmin(dist[i][j], dist[i][j-1] + 1);
                }
            }
        }
    }
    
    // Second pass: bottom-right to top-left
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (grid[i][j] == 0) {
                if (i < n - 1) {
                    dist[i][j] = fmin(dist[i][j], dist[i+1][j] + 1);
                }
                if (j < n - 1) {
                    dist[i][j] = fmin(dist[i][j], dist[i][j+1] + 1);
                }
                maxDist = fmax(maxDist, dist[i][j]);
            }
        }
    }
    
    return (maxDist == n * n) ? -1 : maxDist;       
}
