// Source: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer matrix grid and an integer k.
//
// Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to k.
//
// Example:
// Input: grid = [[7,6,3],[6,6,1]], k = 18
// Output: 4
// Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.
//
// Constraints:
// m == grid.length 
// 	n == grid[i].length
// 	1 <= n, m <= 1000 
// 	0 <= grid[i][j] <= 1000
// 	1 <= k <= 109
//

int countSubmatrices(int** grid, int gridSize, int* gridColSize, int k) {
    int count = 0;
    int rows = gridSize;
    int cols = gridColSize[0];
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int sum = 0;
            for (int i = 0; i <= r; i++) {
                for (int j = 0; j <= c; j++) {
                    sum += grid[i][j];
                }
            }
            if (sum <= k) {
                count++;
            }
        }
    }
    
    return count;       
}
