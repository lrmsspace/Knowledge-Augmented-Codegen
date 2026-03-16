// Source: https://leetcode.com/problems/count-sub-islands/   |   Difficulty: Medium
//
// Problem Description:
// You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.
//
// An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.
//
// Return the number of islands in grid2 that are considered sub-islands.
//
// Example:
// Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
// Output: 3
// Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
// The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.
//
// Constraints:
// m == grid1.length == grid2.length
// 	n == grid1[i].length == grid2[i].length
// 	1 <= m, n <= 500
// 	grid1[i][j] and grid2[i][j] are either 0 or 1.
//

int countSubIslands(int** grid1, int grid1Size, int* grid1ColSize, int** grid2, int grid2Size, int* grid2ColSize) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int rows = grid1Size;
    int cols = grid1ColSize[0];
    int subIslandCount = 0;

    void dfs(int r, int c, int* isSubIsland) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid2[r][c] == 0) {
            return;
        }
        if (grid1[r][c] == 0) {
            *isSubIsland = 0;
        }
        grid2[r][c] = 0; // Mark as visited
        for (int i = 0; i < 4; i++) {
            dfs(r + directions[i][0], c + directions[i][1], isSubIsland);
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid2[r][c] == 1) {
                int isSubIsland = 1;
                dfs(r, c, &isSubIsland);
                subIslandCount += isSubIsland;
            }
        }
    }

    return subIslandCount;      
}
