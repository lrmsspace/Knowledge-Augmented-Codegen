// Source: https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
//
//
// 	A land cell if grid[r][c] = 0, or
// 	A water cell containing grid[r][c] fish, if grid[r][c] > 0.
//
//
// A fisher can start at any water cell (r, c) and can do the following operations any number of times:
//
//
// 	Catch all the fish at cell (r, c), or
// 	Move to any adjacent water cell.
//
//
// Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally, or 0 if no water cell exists.
//
// An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.
//
// Example:
// Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
// Output: 7
// Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	0 <= grid[i][j] <= 10
//

int findMaxFish(int** grid, int gridSize, int* gridColSize) {
    int maxFish = 0;
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    void dfs(int r, int c, int* currentFish) {
        if (r < 0 || r >= gridSize || c < 0 || c >= gridColSize[0] || grid[r][c] == 0) {
            return;
        }
        
        *currentFish += grid[r][c];
        int temp = grid[r][c];
        grid[r][c] = 0; // Mark as visited
        
        for (int i = 0; i < 4; i++) {
            dfs(r + directions[i][0], c + directions[i][1], currentFish);
        }
        
        grid[r][c] = temp; // Backtrack
    }
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] > 0) {
                int currentFish = 0;
                dfs(i, j, &currentFish);
                if (currentFish > maxFish) {
                    maxFish = currentFish;
                }
            }
        }
    }
    
    return maxFish;     
}
