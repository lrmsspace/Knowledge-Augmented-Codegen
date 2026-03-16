// Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
//
// A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
//
// The product of a path is defined as the product of all the values in the path.
//
// Return the maximum number of trailing zeros in the product of a cornered path found in grid.
//
// Note:
//
//
// 	Horizontal movement means moving in either the left or right direction.
// 	Vertical movement means moving in either the up or down direction.
//
// Example:
// Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
// Output: 3
// Explanation: The grid on the left shows a valid cornered path.
// It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
// It can be shown that this is the maximum trailing zeros in the product of a cornered path.
//
// The grid in the middle is not a cornered path as it has more than one turn.
// The grid on the right is not a cornered path as it requires a return to a previously visited cell.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 1000
//

class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> count2(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> count5(m + 1, vector<int>(n + 1, 0));

        auto countFactors = [](int num, int factor) {
            int count = 0;
            while (num % factor == 0) {
                num /= factor;
                count++;
            }
            return count;
        };

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int val = grid[i - 1][j - 1];
                int c2 = countFactors(val, 2);
                int c5 = countFactors(val, 5);

                count2[i][j] = count2[i - 1][j] + count2[i][j - 1] - count2[i - 1][j - 1] + c2;
                count5[i][j] = count5[i - 1][j] + count5[i][j - 1] - count5[i - 1][j - 1] + c5;
            }
        }

        int maxZeros = 0;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int c2 = countFactors(grid[i - 1][j - 1], 2);
                int c5 = countFactors(grid[i - 1][j - 1], 5);

                // Up + Left
                int total2 = count2[i][j] + count2[i][n] - count2[i][j] + count2[m][j] - count2[i][j] + c2;
                int total5 = count5[i][j] + count5[i][n] - count5[i][j] + count5[m][j] - count5[i][j] + c5;
                maxZeros = max(maxZeros, min(total2, total5));
                // Up + Right
                total2 = count2[i][j] + count2[i][n] - count2[i][j - 1] + count2[m][j - 1] - count2[i][j - 1] + c2;
                total5 = count5[i][j] + count5[i][n] - count5[i][j - 1] + count5[m][j - 1] - count5[i][j - 1] + c5;
                maxZeros = max(maxZeros, min(total2, total5));
                // Down + Left
                total2 = count2[m][j] - count2[i - 1][j] + count2[i - 1][n] - count2[i - 1][j] + count2[m][j] - count2[i][j] + c2;
                total5 = count5[m][j] - count5[i - 1][j] + count5[i - 1][n] - count5[i - 1][j] + count5[m][j] - count5[i][j] + c5;
                maxZeros = max(maxZeros, min(total2, total5));
                // Down + Right
                total2 = count2[m][j] - count2[i - 1][j] + count2[i - 1][n] - count2[i - 1][j - 1] + count2[m][j - 1] - count2[i][j - 1] + c2;
                total5 = count5[m][j] - count5[i - 1][j] + count5[i - 1][n] - count5[i - 1][j - 1] + count5[m][j - 1] - count5[i][j - 1] + c5;
                maxZeros = max(maxZeros, min(total2, total5));  
            }
        }
        return maxZeros;    
    }
};
