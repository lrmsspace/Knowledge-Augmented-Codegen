// Source: https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/   |   Difficulty: Easy
//
// Problem Description:
// You are given a m x n matrix grid consisting of non-negative integers.
//
// In one operation, you can increment the value of any grid[i][j] by 1.
//
// Return the minimum number of operations needed to make all columns of grid strictly increasing.
//
// Example:
// Input: grid = [[3,2],[1,3],[3,4],[0,1]]
//
// Output: 15
//
// Explanation:
//
//
// 	To make the 0th column strictly increasing, we can apply 3 operations on grid[1][0], 2 operations on grid[2][0], and 6 operations on grid[3][0].
// 	To make the 1st column strictly increasing, we can apply 4 operations on grid[3][1].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	0 <= grid[i][j] < 2500
//

class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int totalOperations = 0;

        for (int col = 0; col < n; ++col) {
            for (int row = 1; row < m; ++row) {
                if (grid[row][col] <= grid[row - 1][col]) {
                    int requiredValue = grid[row - 1][col] + 1;
                    totalOperations += requiredValue - grid[row][col];
                    grid[row][col] = requiredValue;
                }
            }
        }

        return totalOperations;         
    }
};
