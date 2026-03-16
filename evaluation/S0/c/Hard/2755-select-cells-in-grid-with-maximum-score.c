// Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid consisting of positive integers.
//
// You have to select one or more cells from the matrix such that the following conditions are satisfied:
//
//
// 	No two selected cells are in the same row of the matrix.
// 	The values in the set of selected cells are unique.
//
//
// Your score will be the sum of the values of the selected cells.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
//
// Output: 8
//
// Explanation:
//
//
//
// We can select the cells with values 1, 3, and 4 that are colored above.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 10
// 	1 <= grid[i][j] <= 100
//

int maxScore(int** grid, int gridSize, int* gridColSize) {
    int maxScore = 0;
    int used[101] = {0}; // Since grid[i][j] <= 100
    void backtrack(int row, int currentScore) {
        if (row == gridSize) {
            if (currentScore > maxScore) {
                maxScore = currentScore;
            }
            return;
        }
        for (int col = 0; col < gridColSize[row]; ++col) {
            int val = grid[row][col];
            if (!used[val]) {
                used[val] = 1;
                backtrack(row + 1, currentScore + val);
                used[val] = 0;
            }
        }
        // Also consider the option of skipping this row
        backtrack(row + 1, currentScore);
    }
    backtrack(0, 0);
    return maxScore;        
}
