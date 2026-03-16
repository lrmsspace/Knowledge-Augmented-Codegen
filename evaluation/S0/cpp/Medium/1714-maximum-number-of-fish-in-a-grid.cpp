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

class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int maxFish = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] > 0 && !visited[r][c]) {
                    int currentFish = dfs(grid, visited, r, c);
                    maxFish = max(maxFish, currentFish);
                }
            }
        }
        
        return maxFish;         
    }
};
