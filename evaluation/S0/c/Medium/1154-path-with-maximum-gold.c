// Source: https://leetcode.com/problems/path-with-maximum-gold/   |   Difficulty: Medium
//
// Problem Description:
// In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
//
// Return the maximum amount of gold you can collect under the conditions:
//
//
// 	Every time you are located in a cell you will collect all the gold in that cell.
// 	From your position, you can walk one step to the left, right, up, or down.
// 	You can't visit the same cell more than once.
// 	Never visit a cell with 0 gold.
// 	You can start and stop collecting gold from any position in the grid that has some gold.
//
// Example:
// Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
// Output: 24
// Explanation:
// [[0,6,0],
//  [5,8,7],
//  [0,9,0]]
// Path to get the maximum gold, 9 -> 8 -> 7.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	0 <= grid[i][j] <= 100
// 	There are at most 25 cells containing gold.
//

int getMaximumGold(int** grid, int gridSize, int* gridColSize) {
    int maxGold = 0;
    int directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    
    void dfs(int x, int y, int currentGold) {
        int temp = grid[x][y];
        currentGold += temp;
        if (currentGold > maxGold) {
            maxGold = currentGold;
        }
        grid[x][y] = 0; // Mark as visited
        
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];
            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridColSize[0] && grid[newX][newY] > 0) {
                dfs(newX, newY, currentGold);
            }
        }
        
        grid[x][y] = temp; // Backtrack
    }
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] > 0) {
                dfs(i, j, 0);
            }
        }
    }
    
    return maxGold;     
}
