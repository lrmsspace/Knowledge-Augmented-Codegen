// Source: https://leetcode.com/problems/pacific-atlantic-water-flow/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.
//
// The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
//
// The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
//
// Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
//
// Example:
// Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
// Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
// [0,4]: [0,4] -> Pacific Ocean 
//        [0,4] -> Atlantic Ocean
// [1,3]: [1,3] -> [0,3] -> Pacific Ocean 
//        [1,3] -> [1,4] -> Atlantic Ocean
// [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
//        [1,4] -> Atlantic Ocean
// [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
//        [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean 
//        [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean 
//        [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean 
//        [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
//
// Constraints:
// m == heights.length
// 	n == heights[r].length
// 	1 <= m, n <= 200
// 	0 <= heights[r][c] <= 105
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int m = heightsSize;
    int n = heightsColSize[0];
    
    int** pacific = (int**)malloc(m * sizeof(int*));
    int** atlantic = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++) {
        pacific[i] = (int*)calloc(n, sizeof(int));
        atlantic[i] = (int*)calloc(n, sizeof(int));
    }
    
    void dfs(int** ocean, int x, int y) {
        ocean[x][y] = 1;
        for(int d = 0; d < 4; d++) {
            int newX = x + directions[d][0];
            int newY = y + directions[d][1];
            if(newX >= 0 && newX < m && newY >= 0 && newY < n &&
               ocean[newX][newY] == 0 &&
               heights[newX][newY] >= heights[x][y]) {
                dfs(ocean, newX, newY);
            }
        }
    }
    
    for(int i = 0; i < m; i++) {
        dfs(pacific, i, 0);
        dfs(atlantic, i, n - 1);
    }
    
    for(int j = 0; j < n; j++) {
        dfs(pacific, 0, j);
        dfs(atlantic, m - 1, j);
    }
    
    int** result = (int**)malloc(m * n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * n * sizeof(int));
    *returnSize = 0;
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(pacific[i][j] && atlantic[i][j]) {
                result[*returnSize] = (int*)malloc(2 * sizeof(int));
                result[*returnSize][0] = i;
                result[*returnSize][1] = j;
                (*returnColumnSizes)[*returnSize] = 2;
                (*returnSize)++;
            }
        }
    }
    for(int i = 0; i < m; i++) {
        free(pacific[i]);
        free(atlantic[i]);
    }   
    free(pacific);
    free(atlantic);
    return result;
}
