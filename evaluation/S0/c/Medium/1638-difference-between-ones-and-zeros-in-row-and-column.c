// Source: https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid.
//
// A 0-indexed m x n difference matrix diff is created with the following procedure:
//
//
// 	Let the number of ones in the ith row be onesRowi.
// 	Let the number of ones in the jth column be onesColj.
// 	Let the number of zeros in the ith row be zerosRowi.
// 	Let the number of zeros in the jth column be zerosColj.
// 	diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj
//
//
// Return the difference matrix diff.
//
// Example:
// Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
// Output: [[0,0,4],[0,0,4],[-2,-2,2]]
// Explanation:
// - diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
// - diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
// - diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
// - diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
// - diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
// - diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
// - diff[2][0] = onesRow2 + onesCol0 - zerosRow2 - zerosCol0 = 1 + 1 - 2 - 2 = -2
// - diff[2][1] = onesRow2 + onesCol1 - zerosRow2 - zerosCol1 = 1 + 1 - 2 - 2 = -2
// - diff[2][2] = onesRow2 + onesCol2 - zerosRow2 - zerosCol2 = 1 + 3 - 2 - 0 = 2
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** onesMinusZeros(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    
    int* rowOnes = (int*)calloc(m, sizeof(int));
    int* colOnes = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                rowOnes[i]++;
                colOnes[j]++;
            }
        }
    }
    
    int** diff = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        diff[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            int onesRow = rowOnes[i];
            int onesCol = colOnes[j];
            int zerosRow = n - onesRow;
            int zerosCol = m - onesCol;
            diff[i][j] = onesRow + onesCol - zerosRow - zerosCol;
        }
    }
    
    free(rowOnes);
    free(colOnes);
    
    *returnSize = m;
    return diff;        
}
